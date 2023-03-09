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


}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("square_odom");

  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  auto subscriber = node->create_subscription<nav_msgs::msg::Odometry>("/odom", 10, odom_callback);
  // Esperar a que el nodo obtenga la primera posición y orientación
  rclcpp::spin_some(node);

  for (int i = 0; i < 4; i++) {
    // Guardar la posición y orientación inicial
    x_init = x;
    y_init = y;
    ang_init = ang;


    // Iniciar movimiento
    double dist = 0.0;
    while (rclcpp::ok() && dist < 1.0) {
        rclcpp::spin_some(node);

        // Calcular la distancia recorrida desde el punto inicial
        dist = sqrt(pow(x - x_init, 2) + pow(y - y_init, 2));
        std::cout << "Distancia recorrida: " << dist << std::endl;

        // Avanzar recto
        geometry_msgs::msg::Twist twist;
        twist.linear.x = 0.1;  // Velocidad lineal de 0.1 m/s
        twist.angular.z = 0.0; // Velocidad angular de 0 rad/s
        publisher->publish(twist);

    }

    // Girar 90 grados
    double ang_diff = 0.0;
    while (rclcpp::ok() && std::abs(ang_diff) < 90.0) {
        rclcpp::spin_some(node);

          ang_diff = ang - ang_init;
        std::cout << "Diferencia de ángulo: " << ang_diff << std::endl;

        // Publicar mensaje de control para girar
        geometry_msgs::msg::Twist twist;
        twist.linear.x = 0.0;    // Velocidad lineal nula
        twist.angular.z = 0.2;   // Velocidad angular de 0.2 rad/s
        publisher->publish(twist);
    }
  }
  geometry_msgs::msg::Twist twist;
        twist.linear.x = 0.0;    // Velocidad lineal nula
        twist.angular.z = 0.0;   // Velocidad angular nula
        publisher->publish(twist);
  rclcpp::shutdown();
  return 0;
}
