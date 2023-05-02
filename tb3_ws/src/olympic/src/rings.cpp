#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
#include "turtlesim/srv/teleport_relative.hpp"

using namespace std::chrono_literals;
using turtlesim::srv::SetPen;
using turtlesim::srv::TeleportAbsolute;
using turtlesim::srv::TeleportRelative;

void centrar(std::shared_ptr<rclcpp::Node> node, double altura) {
     // Service SetPen
 auto client_setpen = node->create_client<SetPen>("/turtle1/set_pen"); 

  // Wait for the service to be available
  while (!client_setpen->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for the service. Exiting.");
    }
    RCLCPP_INFO(node->get_logger(), "Service not available, waiting again...");
  }

   // Create a request message for the set_pen service
   auto request = std::make_shared<SetPen::Request>();
   request->r = 255;
   request->g = 0;
   request->b = 0;
   request->width = 3;
   request->off = true;

   // Call the set_pen service
   auto result_future = client_setpen->async_send_request(request);
   rclcpp::spin_until_future_complete(node, result_future);
   auto result_setpen = result_future.get();
    
    // Service teleport abs
 auto client_teleport_abs = node->create_client<TeleportAbsolute>("/turtle1/teleport_absolute"); 

  // Wait for the service to be available
  while (!client_teleport_abs->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for the service. Exiting.");
    }
    RCLCPP_INFO(node->get_logger(), "Service not available, waiting again...");
  }

   // Create a request message for the Teleport service
   auto request_teleport_abs = std::make_shared<TeleportAbsolute::Request>();
   request_teleport_abs->x = 5.5;
   request_teleport_abs->y = altura;
   request_teleport_abs->theta = 0;

   // Call the set_pen service
   auto result_future_teleport_abs = client_teleport_abs->async_send_request(request_teleport_abs);
   rclcpp::spin_until_future_complete(node, result_future_teleport_abs);
   auto result_teleport_abs = result_future_teleport_abs.get();
}

void teleport_rel(std::shared_ptr<rclcpp::Node> node, double linear, double angular) {
    // Service teleport relative
 auto client_teleport = node->create_client<TeleportRelative>("/turtle1/teleport_relative"); 

  // Wait for the service to be available
  while (!client_teleport->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for the service. Exiting.");
    }
    RCLCPP_INFO(node->get_logger(), "Service not available, waiting again...");
  }

   // Create a request message for the Teleport service
   auto request_teleport = std::make_shared<TeleportRelative::Request>();
   request_teleport->linear = linear;
   request_teleport->angular = angular;

   // Call the set_pen service
   auto result_future_teleport = client_teleport->async_send_request(request_teleport);
   rclcpp::spin_until_future_complete(node, result_future_teleport);
   auto result_teleport = result_future_teleport.get();
}

void dibujar(std::shared_ptr<rclcpp::Node> node, std::shared_ptr<rclcpp::Publisher<geometry_msgs::msg::Twist>> publisher, double radius, double vel_linear, int r, int g, int b) {
 geometry_msgs::msg::Twist message;
 rclcpp::WallRate loop_rate(500ms);
    // Service SetPen
 auto client_setpen = node->create_client<SetPen>("/turtle1/set_pen"); 

  // Wait for the service to be available
  while (!client_setpen->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for the service. Exiting.");
    }
    RCLCPP_INFO(node->get_logger(), "Service not available, waiting again...");
  }

   // Create a request message for the set_pen service
   auto request = std::make_shared<SetPen::Request>();
   request->r = r;
   request->g = g;
   request->b = b;
   request->width = 4;
   request->off = false;

   // Call the set_pen service
   auto result_future = client_setpen->async_send_request(request);
   rclcpp::spin_until_future_complete(node, result_future);
   auto result_setpen = result_future.get();

   // Perimetro
   double perimetro = 2 * 3.1416 * radius;
 
   // Iteraciones
   int iteraciones = perimetro/vel_linear/0.5 + 2;
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
}

int main(int argc, char * argv[])
{
 rclcpp::init(argc, argv);
 auto node = rclcpp::Node::make_shared("rings");
 auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
 node->declare_parameter("radius", 1.0);
 rclcpp::WallRate loop_rate(500ms);
 
 double vel_linear = 1;
 double radius = node->get_parameter("radius").get_parameter_value().get<double>();
 
 // Circulo negro
 centrar(node, 5.5 + radius/2);
 dibujar(node, publisher, radius, vel_linear, 0, 0, 0);
 
 // Circulo azul
 centrar(node, 5.5 + radius/2);
 teleport_rel(node, -radius*2 * 1.1, 0);
 dibujar(node, publisher, radius, vel_linear, 0, 0, 255);
 
 // Circulo rojo
 centrar(node, 5.5 + radius/2);
 teleport_rel(node, +radius*2 * 1.1, 0);
 dibujar(node, publisher, radius, vel_linear, 255, 0, 0);
 
 // Circulo amarillo
 centrar(node, 5.5 - radius/2);
 teleport_rel(node, -radius * 1.1, 0);
 dibujar(node, publisher, radius, vel_linear, 255, 255, 0);
 
 // Circulo verde
 centrar(node, 5.5 - radius/2);
 teleport_rel(node, radius * 1.1, 0);
 dibujar(node, publisher, radius, vel_linear, 0, 128, 0);
 
 rclcpp::shutdown();
 return 0;
}

// ros2 run olympic rings --ros-args --param radius:=0.5
