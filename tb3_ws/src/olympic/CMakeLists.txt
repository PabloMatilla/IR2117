cmake_minimum_required(VERSION 3.5)
project(olympic)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(olympic_interfaces REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)

add_executable(rings src/rings.cpp)
target_include_directories(rings PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
    rings
    "rclcpp"
    "std_msgs"
    "geometry_msgs"
    "turtlesim"
)
 
add_executable(parallel_rings src/parallel_rings.cpp)
target_include_directories(parallel_rings PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  parallel_rings
  "rclcpp"
  "std_msgs"
  "geometry_msgs"
  "turtlesim"
)

add_executable(rings_action_server src/rings_action_server.cpp)
ament_target_dependencies(rings_action_server
  rclcpp
  rclcpp_action
  rclcpp_components
  geometry_msgs
  turtlesim
  olympic_interfaces)

add_executable(rings_action_client src/rings_action_client.cpp)
ament_target_dependencies(rings_action_client
  rclcpp
  rclcpp_action
  rclcpp_components
  geometry_msgs
  turtlesim
  olympic_interfaces)
  

install(TARGETS rings
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS parallel_rings
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS
  rings_action_server
  rings_action_client
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
