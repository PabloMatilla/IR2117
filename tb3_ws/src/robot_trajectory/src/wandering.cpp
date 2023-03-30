#define _USE_MATH_DEFINES

#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "std_msgs/msg/string.hpp"
#include <cmath>
#include <unistd.h>


using namespace std::chrono_literals;

double minizq, minder;

void topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg){
    minizq = 3;
    minder = 3;
    for (int i = 0; i < 10; i++)
        if (msg -> ranges[i] < minizq) minizq = msg -> ranges[i];

    for (int i = 350; i < 359; i++)
        if (msg -> ranges[i] < minder) minder = msg -> ranges[i];

    std::cout << "Distancia minima izquierda: " << minizq << std::endl;
    std::cout << "Distancia minima derdecha:  " << minder  << std::endl;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("wandering");
    auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    auto subscriber = node->create_subscription<sensor_msgs::msg::LaserScan>("scan", 10, topic_callback);

    double velocity;
    geometry_msgs::msg::Twist message;
    rclcpp::WallRate loop_rate(10ms);

    while (rclcpp::ok()) {
      while (rclcpp::ok() and (minder > 1 and  minizq > 1)){
        message.linear.x = 0.3;
        message.angular.z = 0;
        publisher->publish(message);
        rclcpp::spin_some(node);
      }

      if (minder < minizq) {
        velocity =  0.2;
      } else {
        velocity = -0.2;
      }

      while (rclcpp::ok() and (minder <= 1 or  minizq <= 1)) {
        message.linear.x = 0;
        message.angular.z = velocity;
        publisher->publish(message);
        rclcpp::spin_some(node);
      }
    }

    rclcpp::shutdown();
    return 0;
}
