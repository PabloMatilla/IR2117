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
  geometry_msgs::msg::Twist message;
  rclcpp::WallRate loop_rate(10ms);

  message.linear.x = 0;
  message.angular.z = 0;
  rclcpp::spin_some(node);
  loop_rate.sleep();
  publisher->publish(message);
  
  
  for(int j = 0; j<4; j++) {
    int i=0, n=1000;
    while (rclcpp::ok() && (i<n)) {
      message.linear.x = 0.1;
      message.angular.z = 0;
      rclcpp::spin_some(node);
      loop_rate.sleep();
      publisher->publish(message);
      i++;
    }
    
    int i2=0, n2=1000 ;
    while (rclcpp::ok() && (i2<n2)) {
      message.linear.x = 0;
      message.angular.z = 0.164;
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

