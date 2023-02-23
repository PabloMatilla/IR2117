#define _USE_MATH_DEFINES

#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cmath>


using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("square");
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  node->declare_parameter("lineal_speed", 0.1);
  node->declare_parameter("angular_speed", M_PI / 20);
  node->declare_parameter("square_length", 1.0);
  geometry_msgs::msg::Twist message;
  rclcpp::WallRate loop_rate(10ms);

  message.linear.x = 0;
  message.angular.z = 0;
  rclcpp::spin_some(node);
  loop_rate.sleep();
  publisher->publish(message);
  
  double lineal_speed = node->get_parameter("lineal_speed").get_parameter_value().get<double>();
  double angular_speed = node->get_parameter("angular_speed").get_parameter_value().get<double>();
  double square_length = node->get_parameter("square_length").get_parameter_value().get<double>();
  
  double linear_iterations = square_length / (0.01 * lineal_speed);
  double angular_iterations = M_PI/2 / (0.01 * angular_speed);
  
  
  for(int j = 0; j<4; j++) {
    int i=0;
    while (rclcpp::ok() && (i<linear_iterations)) {
      message.linear.x = lineal_speed;
      message.angular.z = 0.0;
      rclcpp::spin_some(node);
      loop_rate.sleep();
      publisher->publish(message);
      i++;
    }
    
    int i2=0;
    while (rclcpp::ok() && (i2<angular_iterations)) {
      message.linear.x = 0.0;
      message.angular.z = angular_speed;
      rclcpp::spin_some(node);
      loop_rate.sleep();
      publisher->publish(message);
      i2++;
    }
    message.linear.x = 0;
    message.angular.z = 0;
    rclcpp::spin_some(node);
    loop_rate.sleep();
    publisher->publish(message);
  }
  
  rclcpp::shutdown();
  return 0;
}

