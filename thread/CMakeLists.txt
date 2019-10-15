cmake_minimum_required(VERSION 3.4.1)
project(thread)
add_compile_options(-std=c++11)

include_directories(./include)
aux_source_directory(./src SRC_LIST)
# add_library(my_func ${SRC_LIST})

# target_link_libraries(main my_func)
# find_package (Threads)
add_executable(10recursive_mutex 10recursive_mutex.cpp)
# target_link_libraries (threadjoin ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (10recursive_mutex pthread) # ubuntu下需要连接这个库pthread
