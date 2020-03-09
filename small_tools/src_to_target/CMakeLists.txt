cmake_minimum_required(VERSION 2.8.1)
project(src_to_target)
# add_compile_options(-std=c++11)

include_directories(./include)
# aux_source_directory(./src SRC)
# add_library(${PROJECT_NAME} ${SRC})

add_executable(src_to_target src_to_target.c)

# target_link_libraries(main ${PROJECT_NAME})
