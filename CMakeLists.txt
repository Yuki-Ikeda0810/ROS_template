cmake_minimum_required(VERSION 3.0.2)
project(ros_template_programs)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  roscpp
  rospy
  std_msgs
  message_generation
  pluginlib
  nodelet
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  Expression.msg
)

## Generate services in the 'srv' folder
add_service_files(
  FILES
  Calculation.srv
)

## Generate actions in the 'action' folder
add_action_files(
  FILES
  Timer.action
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  actionlib_msgs std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ros_template_programs
  CATKIN_DEPENDS actionlib actionlib_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(topic_publisher_template src/topic_publisher_template.cpp)
target_link_libraries(topic_publisher_template ${catkin_LIBRARIES})

add_executable(topic_subscriber_template src/topic_subscriber_template.cpp)
target_link_libraries(topic_subscriber_template ${catkin_LIBRARIES})

add_executable(service_client_template src/service_client_template.cpp)
target_link_libraries(service_client_template ${catkin_LIBRARIES})
add_dependencies(service_client_template ${PROJECT_NAME}_generate_messages_cpp)

add_executable(service_server_template src/service_server_template.cpp)
target_link_libraries(service_server_template ${catkin_LIBRARIES})
add_dependencies(service_server_template ${PROJECT_NAME}_generate_messages_cpp)

add_executable(action_client_template src/action_client_template.cpp)
target_link_libraries(action_client_template ${catkin_LIBRARIES})
add_dependencies(action_client_template ${PROJECT_NAME}_generate_messages_cpp)

add_executable(action_server_template src/action_server_template.cpp)
target_link_libraries(action_server_template ${catkin_LIBRARIES})
add_dependencies(action_server_template ${PROJECT_NAME}_generate_messages_cpp)

add_library(${PROJECT_NAME} src/nodelets/plugin_nodelet_topic_publisher_template.cpp
                            src/nodelets/plugin_nodelet_topic_subscriber_template.cpp )
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})