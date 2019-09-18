project(cppSTL)
cmake_minimum_required(VERSION 3.10.0)
add_compile_options(-std=c++11)

include_directories(./include)
# aux_source_directory(./src SRC_LIST)
# add_library(mysrc ${SRC_LIST})

add_executable(main main.cpp)
