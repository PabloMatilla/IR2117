#include <iostream>
#include <chrono>
#include <random>
#include <cstdio>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "example_interfaces/msg/bool.hpp"

using namespace std::chrono_literals;

bool front, left, right;

void callback_front(const example_interfaces::msg::Bool::SharedPtr msg) {
    front = msg->data;
}

void callback_left(const example_interfaces::msg::Bool::SharedPtr msg) {
    left = msg->data;
}

void callback_right(const example_interfaces::msg::Bool::SharedPtr msg) {
    right = msg->data;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("avoidance");
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  auto subs_front = node->create_subscription<example_interfaces::msg::Bool>("/front/obstacle", 10, callback_front);
  auto subs_left = node->create_subscription<example_interfaces::msg::Bool>("/left/obstacle", 10, callback_left);
  auto subs_right = node->create_subscription<example_interfaces::msg::Bool>("/right/obstacle", 10, callback_right);
  geometry_msgs::msg::Twist message;
  rclcpp::WallRate loop_rate(50ms);
  
  while (rclcpp::ok()) {
      // Decision aleatoria en el caso de deteccion frontal
      std::random_device rd;
      std::mt19937 gen(rd());
      std::bernoulli_distribution d(0.5);
      bool resultado = d(gen);

    while (rclcpp::ok() and not front and not left and not right) {
        message.linear.x = 0.3;
        message.angular.z = 0;
        printf("Publicando... (FORWARD) \n");
        publisher -> publish(message);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
    while (rclcpp::ok() and left) {
        message.linear.x = 0;
        message.angular.z = -0.2;
        printf("Publicando... (LEFT) \n");        
        publisher -> publish(message);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
    while (rclcpp::ok() and right) {
        message.linear.x = 0;
        message.angular.z = 0.2;
        printf("Publicando... (RIGHT) \n");                
        publisher -> publish(message);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
    while (rclcpp::ok() and front) {
        message.linear.x = 0;
        message.angular.z = 0.2 * resultado;

        printf("Publicando... (FRONT) \n");                        
        publisher -> publish(message);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

  }
  

  rclcpp::shutdown();
  return 0;
}

