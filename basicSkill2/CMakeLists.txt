cmake_minimum_required(VERSION 3.4.1)
add_compile_options(-std=c++11)
project(basicSkill2)


aux_source_directory(./src SRC_LIST)
include_directories(./include)

# add_library(my_func ${SRC_LIST})

# add_executable(conversionFunction conversionFunction.cpp)
# target_link_libraries(singleton my_func)

add_executable(pointer_like_class pointer_like_class.cpp)

