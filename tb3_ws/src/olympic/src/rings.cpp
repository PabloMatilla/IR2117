#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/set_pen.hpp"

using namespace std::chrono_literals;
using turtlesim::srv::SetPen;

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
 

 //auto node = rclcpp::Node::make_shared("set_pen_client");
 auto client = node->create_client<SetPen>("/turtle1/set_pen"); 

  // Wait for the service to be available
  while (!client->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for the service. Exiting.");
      return 1;
    }
    RCLCPP_INFO(node->get_logger(), "Service not available, waiting again...");
  }

   // Create a request message for the set_pen service
   auto request = std::make_shared<SetPen::Request>();
   request->r = 255;
   request->g = 0;
   request->b = 0;
   request->width = 3;
   request->off = false;

   // Call the set_pen service
   auto result_future = client->async_send_request(request);
   rclcpp::spin_until_future_complete(node, result_future);
   auto result = result_future.get();

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
