#define _USE_MATH_DEFINES

#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <iostream>

void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
    std::cout << msg << std::endl;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("square_odom");
  
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  auto subscriber = node->create_subscription<nav_msgs::msg::Odometry>("/odom", 10, odom_callback);
  
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

