#define _USE_MATH_DEFINES

#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "std_msgs/msg/string.hpp"
#include <cmath>


using namespace std::chrono_literals;

void topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg){
    std::cout << "Grado 0: " << msg->ranges[0] << std::endl;
    std::cout << "Grado 90: " << msg->ranges[90] << std::endl;
    std::cout << "Grado 180: " << msg->ranges[180] << std::endl;
    std::cout << "Grado 270: " << msg->ranges[270] << "\n"<< std::endl;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("wandering");
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  auto subscriber = node->create_subscription<sensor_msgs::msg::LaserScan>("scan", 10, topic_callback);
  std_msgs::msg::String s;

  geometry_msgs::msg::Twist message;
  rclcpp::WallRate loop_rate(10ms);
  
  while (rclcpp::ok()){
    message.linear.x = 0;
    message.angular.z = 0;
    publisher->publish(message);
    rclcpp::spin_some(node);
  }
  
  rclcpp::shutdown();
  return 0;
}
