cmake_minimum_required(VERSION 3.10)
project(HelloTriangle)
set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(triangle main.cpp glad.c)
target_include_directories(triangle PRIVATE include)
target_link_libraries(triangle PRIVATE glfw OpenGL::GL ${CMAKE_DL_LIBS})