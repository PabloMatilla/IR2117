from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='turtlesim',
            executable='turtlesim_node'
            ),
        Node(
            package='robot_trajectory',
            executable='square',
            remappings=[
                ('/cmd_vel', 'turtle1/cmd_vel'),
            ],
            parameters=[
                {"lineal_speed": 0.8},
                {"angular_speed": 1.5},
                {"square_lenght": 2.4}
                ]
            )
        ])
