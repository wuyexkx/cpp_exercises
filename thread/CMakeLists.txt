cmake_minimum_required(VERSION 3.4.1)
project(thread)
add_compile_options(-std=c++11)

include_directories(./include)
aux_source_directory(./src SRC_LIST)
# add_library(my_func ${SRC_LIST})

# target_link_libraries(main my_func)

add_executable(lock lock.cpp)