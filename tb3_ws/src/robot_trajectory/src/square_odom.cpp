#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include <iostream>
#include <cmath>

double x_init, y_init, ang_init;
double x, y;
double ang;

void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
    // Obtener la posición x y y
    x = msg->pose.pose.position.x;
    y = msg->pose.pose.position.y;

    // Obtener la orientación como cuaternión
    geometry_msgs::msg::Quaternion orientation = msg->pose.pose.orientation;

    // Convertir cuaternión a ángulos de Euler
    tf2::Quaternion quat;
    tf2::convert(orientation, quat);
    double roll, pitch, yaw;
    tf2::Matrix3x3(quat).getRPY(roll, pitch, yaw);

    // Obtener el ángulo en grados y mostrarlo
    ang = yaw * 180.0 / M_PI;

    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "Angulo: " << ang << std::endl;

    // Calcular la distancia recorrida desde el punto inicial
    double dist = sqrt(pow(x - x_init, 2) + pow(y - y_init, 2));
    std::cout << "Diferencia pos: " << dist << std::endl;

    // Calcular la diferencia de ángulo desde el ángulo inicial
    double ang_diff = ang - ang_init;
    std::cout << "Diferencia angulo: " << ang_diff << std::endl << std::endl;

}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("square_odom");

  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  auto subscriber = node->create_subscription<nav_msgs::msg::Odometry>("/odom", 10, odom_callback);

  // Esperar a que el nodo obtenga la primera posición y orientación
  while (rclcpp::ok() && (x_init == 0.0 && y_init == 0.0 && ang_init == 0.0)) {
      rclcpp::spin_some(node);
  }

  // Guardar la posición y orientación inicial
  x_init = x;
  y_init = y;
  ang_init = ang;


  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

