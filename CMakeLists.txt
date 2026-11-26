cmake_minimum_required(VERSION 3.8)
project(entri_ros2_srvcli_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/RobotTask.srv"
)

add_executable(service_node src/service_node.cpp)
ament_target_dependencies(service_node rclcpp std_srvs)
rosidl_target_interfaces(service_node ${PROJECT_NAME} "rosidl_typesupport_cpp")

add_executable(client_node src/client_node.cpp)
ament_target_dependencies(client_node rclcpp std_srvs)
rosidl_target_interfaces(client_node ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS
  service_node
  client_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
