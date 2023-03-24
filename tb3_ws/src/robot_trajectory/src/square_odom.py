from launch import LaunchDescription
from launch_ros.actions import Node
from gazebo_ros.actions import SpawnEntity

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            arguments=['-entity', 'empty_world', '-file', 'path/to/empty.world']
        ),
        Node(
            package='robot_trajectory',
            executable='square_odom',

            parameters=[
                {"lineal_speed": 0.8},
                {"angular_speed": 1.5},
                {"square_lenght": 2.4}
            ]
        ),
        Node(
            package='gazebo_ros',
            executable='gzclient',
            output='screen'
        )
    ])
