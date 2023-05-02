#include <chrono>
#include <vector>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "turtlesim/srv/spawn.hpp"

using namespace std::chrono_literals;
using turtlesim::srv::SetPen;
using turtlesim::srv::TeleportAbsolute;
using turtlesim::srv::Spawn;


int main(int argc, char * argv[])
{
 rclcpp::init(argc, argv);
 auto node = rclcpp::Node::make_shared("parallel_rings");
 node->declare_parameter("radius", 1.0);
 rclcpp::WallRate loop_rate(500ms);
 
 double vel_linear = 1;
 double radius = node->get_parameter("radius").get_parameter_value().get<double>();

 // Perimetro
 double perimetro = 2 * 3.1416 * radius;
 
 // Iteraciones
  int iteraciones = perimetro/vel_linear/0.5 + 2;

  std::vector<std::string> name = {"turtle1", "turtle2", "turtle3", "turtle4", "turtle5"};
  std::vector<double> x = {5.5, 5.5 - radius*2 * 1.1, 5.5 + radius*2 * 1.1, 5.5 - radius * 1.1, 5.5 + radius * 1.1};
  std::vector<double> y = {5.5 + radius/2, 5.5 + radius/2, 5.5 + radius/2, 5.5 - radius/2, 5.5 - radius/2};
  std::vector<int> r = {0, 0, 255, 255, 0};
  std::vector<int> g = {0, 0, 0, 255, 128};
  std::vector<int> b = {0, 255, 0, 0, 0};

 // Cambiamos posicion del turtle1
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
   request_teleport_abs->y = 5.5 +radius/2;
   request_teleport_abs->theta = 0;

   // Call the set_pen service
   auto result_future_teleport_abs = client_teleport_abs->async_send_request(request_teleport_abs);
   rclcpp::spin_until_future_complete(node, result_future_teleport_abs);
   auto result_teleport_abs = result_future_teleport_abs.get();

  
 for (int i = 1; i < 5; i++) {
  // Creamos una solicitud de servicio para spawnear una nueva instancia de turtlesim
  auto spawn_client = node->create_client<turtlesim::srv::Spawn>("spawn");
    while (!spawn_client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(node->get_logger(), "Waiting for the service to appear...");
  }

  auto request_spawm = std::make_shared<turtlesim::srv::Spawn::Request>();
  request_spawm->name = name[i];
  request_spawm->x = x[i];
  request_spawm->y = y[i];
  request_spawm->theta = 0.0;

  auto future = spawn_client->async_send_request(request_spawm);

  // Esperar hasta que el servicio de spawn responda
  if (rclcpp::spin_until_future_complete(node, future) == rclcpp::FutureReturnCode::SUCCESS) {
    auto response = future.get();
  } else {
    RCLCPP_ERROR(node->get_logger(), "Failed to spawn turtle %s", name[i].c_str());
  }
 }

 for(int i = 0; i < 5; i++){
  // Service SetPen
  auto client_setpen = node->create_client<SetPen>("/" + name[i] + "/set_pen"); 

  // Wait for the service to be available
  while (!client_setpen->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for the service. Exiting.");
    }
    RCLCPP_INFO(node->get_logger(), "Service not available, waiting again...");
  }

   // Create a request message for the set_pen service
   auto request = std::make_shared<SetPen::Request>();
   request->r = r[i];
   request->g = g[i];
   request->b = b[i];
   request->width = 4;
   request->off = false;

   // Call the set_pen service
   auto result_future = client_setpen->async_send_request(request);
   rclcpp::spin_until_future_complete(node, result_future);
   auto result_setpen = result_future.get();

  loop_rate.sleep();
 }

 int count = 0;
 geometry_msgs::msg::Twist message;

 auto publisher1 = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
 auto publisher2 = node->create_publisher<geometry_msgs::msg::Twist>("/turtle2/cmd_vel", 10);
 auto publisher3 = node->create_publisher<geometry_msgs::msg::Twist>("/turtle3/cmd_vel", 10);
 auto publisher4 = node->create_publisher<geometry_msgs::msg::Twist>("/turtle4/cmd_vel", 10);
 auto publisher5 = node->create_publisher<geometry_msgs::msg::Twist>("/turtle5/cmd_vel", 10);

 while (rclcpp::ok() and count < iteraciones) {
    message.linear.x = vel_linear;
    message.angular.z = vel_linear/radius;
    publisher1->publish(message);
    publisher2->publish(message);
    publisher3->publish(message);
    publisher4->publish(message);
    publisher5->publish(message);
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
