#include "rclcpp/rclcpp.hpp"
#include "entri_ros2_srvcli_cpp/srv/robot_task.hpp"

#include <chrono>
#include <memory>

using namespace std::chrono_literals;

class RobotTaskClient : public rclcpp::Node
{
public:
    RobotTaskClient() : Node("robot_task_client")
    {
        client_ = this->create_client<
            entri_ros2_srvcli_cpp::srv::RobotTask>(
            "allocate_robot_task");
    }

    void send_request()
    {
        while (!client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                return;
            }

            RCLCPP_INFO(this->get_logger(), "Waiting for service...");
        }

        auto request =
            std::make_shared<entri_ros2_srvcli_cpp::srv::RobotTask::Request>();

        request->task_id = 42;
        request->task_name = "Move_To_A";

        auto future = client_->async_send_request(request);

        if (rclcpp::spin_until_future_complete(
            this->get_node_base_interface(), future.future) ==
        rclcpp::FutureReturnCode::SUCCESS) {
    
        auto response = future.future.get();

                RCLCPP_INFO(
                    this->get_logger(),
                    "Task allocation status: %s. Response: %s",
                    response->success ? "True" : "False",
                    response->task_response.c_str());
        } else {
            RCLCPP_ERROR(
                this->get_logger(),
                "Failed to receive task allocation response.");
        }
    }

private:
    rclcpp::Client<
        entri_ros2_srvcli_cpp::srv::RobotTask>::SharedPtr client_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<RobotTaskClient>();
    node->send_request();

    rclcpp::shutdown();
    return 0;
}