cmake_minimum_required(VERSION 3.4.1)
project(thread)
add_compile_options(-std=c++11)

include_directories(./include)
aux_source_directory(./src SRC_LIST)
# add_library(my_func ${SRC_LIST})

# target_link_libraries(main my_func)
# find_package (Threads)
add_executable(11fake_awake_thread_pool_nums 11fake_awake_thread_pool_nums.cpp)
# target_link_libraries (threadjoin ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (11fake_awake_thread_pool_nums pthread) # ubuntu下需要连接这个库pthread
