#include "rclcpp/rclcpp.hpp"
#include "entri_ros2_srvcli_cpp/srv/robot_task.hpp"
#include <functional>
#include <memory>

class RobotTaskService : public rclcpp::Node
{
public:
    RobotTaskService() : Node("robot_task_service")
    {
        service_ = this->create_service<
            entri_ros2_srvcli_cpp::srv::RobotTask>(
            "allocate_robot_task",
            std::bind(
                &RobotTaskService::allocate_task,
                this,
                std::placeholders::_1,
                std::placeholders::_2));
    }

private:
    void allocate_task(
        const std::shared_ptr<entri_ros2_srvcli_cpp::srv::RobotTask::Request> request,
        std::shared_ptr<entri_ros2_srvcli_cpp::srv::RobotTask::Response> response)
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Incoming request: task_id=%d, task_name=%s",
            request->task_id,
            request->task_name.c_str());

        if (request->task_id % 2 == 0) {
            response->success = true;
            response->task_response =
                "Task " + request->task_name + " allocated successfully.";
        } else {
            response->success = false;
            response->task_response =
                "Task " + request->task_name + " rejected.";
        }
    }

    rclcpp::Service<
        entri_ros2_srvcli_cpp::srv::RobotTask>::SharedPtr service_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RobotTaskService>());
    rclcpp::shutdown();
    return 0;
}
