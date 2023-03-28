from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
    return LaunchDescription([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([
                "/opt/ros/foxy/share/turtlebot3_gazebo/launch/empty_world.launch.py"
            ])
        ),
        Node(
            package='robot_trajectory',
            executable='square',
            parameters=[
                {"lineal_speed": 0.8},
                {"angular_speed": 1.5},
                {"square_lenght": 2.4}
            ]
        )
    ])
