#define _USE_MATH_DEFINES

#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "std_msgs/msg/string.hpp"
#include <cmath>
#include <unistd.h>


using namespace std::chrono_literals;

double minizq = 1000;
double minder = 1000;

void topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg){
    for (int i = 0; i < 10; i++) {
        if (msg -> ranges[i] < minizq) {
          minizq = msg -> ranges[i];
          std::cout << "Distancia min izq: " << minizq << std::endl;
        }
    }
    for (int i = 350; i < 359; i++) {
        if (msg -> ranges[i] < minder) {
          minder = msg -> ranges[i];
          std::cout << "Distancia min der: " << minder  << std::endl;
        }
    }
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
    message.linear.x = 0.3;
    message.angular.z = 0;
    publisher->publish(message);
    rclcpp::spin_some(node);
    bool turn = true;

    while (rclcpp::ok() and minizq < 1) {
      message.linear.x = 0;
      message.angular.z = 0.2;
      publisher->publish(message);
      rclcpp::spin_some(node);
      //sleep(5);
    }
    /*^
    while (rclcpp::ok() and minder < 1) {
      message.linear.x = 0.0;
      message.angular.z = -0.2;
      publisher->publish(message);
      rclcpp::spin_some(node);
    }
    */


  }
  
  rclcpp::shutdown();
  return 0;
}
