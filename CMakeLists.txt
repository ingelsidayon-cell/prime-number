cmake_minimum_required(VERSION 3.14)  # C++20 support available in CMake 3.14+
project(prime-number)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(prime-number prime-number.cpp)
