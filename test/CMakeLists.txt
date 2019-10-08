project(TEST)
cmake_minimum_required(VERSION 3.4.1)
add_compile_options(-std=c++11)

include_directories(./include)

add_executable(loop_list_main loop_list_main.cpp)

