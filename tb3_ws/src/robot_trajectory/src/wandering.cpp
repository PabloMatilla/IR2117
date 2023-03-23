#define _USE_MATH_DEFINES

#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "std_msgs/msg/string.hpp"
#include <cmath>


using namespace std::chrono_literals;

void callback_function(const sensor_msgs::msg::LaserScan::SharedPtr msg){
    std::cout << "Grado 0" << msg << std::endl;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("wandering");
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 0);
  auto subscriber = node->create_subscription<sensor_msgs::msg::LaserScan>("laser_scan", 10, callback_function);
  std_msgs::msg::s

  geometry_msgs::msg::Twist message;
  rclcpp::WallRate loop_rate(10ms);
  
  while (rclcpp::ok()){
    message.linear.x = 0;
    message.angular.z = 0;
    rclcpp::spin_some(node);
    loop_rate.sleep();
    publisher->publish(message);
  }
  
  rclcpp::shutdown();
  return 0;
}
