cmake_minimum_required(VERSION 3.4.1)
add_compile_options(-std=c++11)
project(class_constructor_copy)


aux_source_directory(./src SRC_LIST)
include_directories(./include)

add_library(my_func ${SRC_LIST})


add_executable(main main.cpp)
target_link_libraries(main my_func)

