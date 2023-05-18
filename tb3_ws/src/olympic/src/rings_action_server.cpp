#include <inttypes.h>
#include <chrono>
#include <memory>
#include <vector>
#include "olympic_interfaces/action/rings.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
#include "turtlesim/srv/teleport_relative.hpp"

using Rings = 
  olympic_interfaces::action::Rings;

using GoalHandleRings = 
  rclcpp_action::ServerGoalHandle<Rings>;

  rclcpp_action::GoalResponse handle_goal(
  const rclcpp_action::GoalUUID & uuid, 
  std::shared_ptr<const Rings::Goal> goal)
{
  RCLCPP_INFO(rclcpp::get_logger("server"), 
    "Got goal request with radius %f", goal->radius);
  (void)uuid;
  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

using namespace std::chrono_literals;
using turtlesim::srv::SetPen;
using turtlesim::srv::TeleportAbsolute;
using turtlesim::srv::TeleportRelative;
using namespace std::chrono_literals;

rclcpp_action::CancelResponse handle_cancel(
  const std::shared_ptr<GoalHandleRings> goal_handle)
{
  RCLCPP_INFO(rclcpp::get_logger("server"), 
    "Got request to cancel goal");
  (void)goal_handle;
  return rclcpp_action::CancelResponse::ACCEPT;
}

void execute(const std::shared_ptr<GoalHandleRings>);

void handle_accepted(
  const std::shared_ptr<GoalHandleRings> goal_handle)
{
  std::thread{execute, goal_handle}.detach();
}


void execute(
  const std::shared_ptr<GoalHandleRings> goal_handle)
{
  RCLCPP_INFO(rclcpp::get_logger("server"), 
    "Executing goal");
  const auto goal = goal_handle->get_goal();
  auto feedback = std::make_shared<Rings::Feedback>();
  auto result = std::make_shared<Rings::Result>();
  auto & drawing_ring = feedback->drawing_ring;
  auto & ring_angle = feedback->ring_angle;

  float radius = goal->radius; 
  auto node = rclcpp::Node::make_shared("rings");
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
  geometry_msgs::msg::Twist message;
  float v_angular = 1.0;
  float v_linear  = radius * v_angular;
  int numero, iterations = 2*M_PI / (v_angular * 0.1);
  
  rclcpp::WallRate loop_rate(100ms);
  
  std::vector<int> r = {0, 0, 255, 255, 0};
  std::vector<int> g = {0, 0, 0, 255, 128};
  std::vector<int> b = {0, 255, 0, 0, 0};
	
  std::vector<double> x = {-2.2, 0, 2.2, -1.2, 1.2};
  std::vector<double> y = {0, 0, 0, -1, -1};
	
  // SetPen service
  rclcpp::Client<SetPen>::SharedPtr client_set_pen =
      node->create_client<SetPen>("/turtle1/set_pen");
  auto request_set_pen = std::make_shared<SetPen::Request>();

  // TeleportAbsolute service
  rclcpp::Client<TeleportAbsolute>::SharedPtr client_teleport_absolute =
	node->create_client<TeleportAbsolute>("/turtle1/teleport_absolute");
  auto request_teleport_absolute = std::make_shared<TeleportAbsolute::Request>();
  
  // Begin the loop
  for (int i = 0; i < 5; i++) {
    if (goal_handle->is_canceling()) {
      goal_handle->canceled(result);
      RCLCPP_INFO(rclcpp::get_logger("server"), 
      "Goal Canceled");
      return;
    }
    // Change colors and disable pen
    request_set_pen->r = r[i];
    request_set_pen->g = g[i];
    request_set_pen->b = b[i];
    request_set_pen->width = 5 * radius;
    request_set_pen->off = 1;
    
    auto result_set_pen = client_set_pen->async_send_request(request_set_pen);
    
    // Circle absolute position
   request_teleport_absolute = std::make_shared<TeleportAbsolute::Request>();
   request_teleport_absolute->x = 5.5 + x[i] * radius;
   request_teleport_absolute->y = 5.5 + y[i] * radius;
   request_teleport_absolute->theta = 0;

    auto result_teleport_absolute = client_teleport_absolute->async_send_request(request_teleport_absolute);

    // Publish feedback (ring and angle we are currently at)
    drawing_ring = i+1;
    ring_angle = 0.0;
    
    goal_handle->publish_feedback(feedback);
    RCLCPP_INFO(rclcpp::get_logger("server"), 
       "Publish Feedback");
    
    // Turn pen back on
    request_set_pen->off = 0;
    result_set_pen = client_set_pen->async_send_request(request_set_pen);
		
    // Draw the circle
    numero = 0;
    while (rclcpp::ok() && (numero <= iterations)) {
	message.linear.x = v_linear;
	message.angular.z = v_angular;
	publisher->publish(message);
	numero++;

      ring_angle =  numero * 360/iterations; 
      goal_handle->publish_feedback(feedback);
      RCLCPP_INFO(rclcpp::get_logger("server"), 
        "Publish Feedback");
      loop_rate.sleep();}
      message.linear.x = 0.0;
      message.angular.z = 0.0;
      publisher->publish(message);
      loop_rate.sleep();
  }

  if (rclcpp::ok()) {
    //result->drawing_ring = drawing_ring;
    goal_handle->succeed(result);
    RCLCPP_INFO(rclcpp::get_logger("server"), 
      "All rings completed");
  }
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("action_server");
  auto action_server = 
    rclcpp_action::create_server<Rings>(node,
      "rings",
      handle_goal,
      handle_cancel,
      handle_accepted);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
