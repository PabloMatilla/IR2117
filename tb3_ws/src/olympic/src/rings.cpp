#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
 rclcpp::init(argc, argv);
 auto node = rclcpp::Node::make_shared("rings");
 auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
 node->declare_parameter("radius", 1.0);
 geometry_msgs::msg::Twist message;
 rclcpp::WallRate loop_rate(500ms);
 
 double vel_linear = 1;
 double radius = node->get_parameter("radius").get_parameter_value().get<double>();
 
 // Perimetro
 double perimetro = 2 * 3.1416 * radius;
 
 // Iteraciones
 int iteraciones = perimetro/vel_linear/0.5;
 int count = 0;
 
 while (rclcpp::ok() and count < iteraciones) {
   message.linear.x = vel_linear;
   message.angular.z = vel_linear/radius;
   publisher->publish(message);
   rclcpp::spin_some(node);
   loop_rate.sleep();
   count++;
 }
 message.linear.x = 0;
 message.angular.z = 0;
 rclcpp::shutdown();
 return 0;
}

// ros2 run olympic rings --ros-args --param radius:=0.5
