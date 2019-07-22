cmake_minimum_required(VERSION 3.4.1)
add_compile_options(-std=c++11)
project(class_constructor_copy)


aux_source_directory(./src SRC_LIST)
include_directories(./include)

add_library(my_func ${SRC_LIST})


# add_executable(clsWithoutPointer_main clsWithoutPointer_main.cpp)
# target_link_libraries(clsWithoutPointer_main my_func)

# add_executable(clsWithPointer_main clsWithPointer_main.cpp)
# target_link_libraries(clsWithPointer_main my_func)

add_executable(heap_stack_main heap_stack_main.cpp)
target_link_libraries(heap_stack_main my_func)
