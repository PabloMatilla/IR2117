cmake_minimum_required(VERSION 3.0)
project(eigen_sta)

# Agregar la ruta a la carpeta que contiene la librería Eigen
include_directories("$ENV{HOME}/Documents/eigen3.4")

# Crear un ejecutable para median
add_executable(median median.cpp utils.cpp)

# Crear un ejecutable para mode
add_executable(mode mode.cpp utils.cpp)
