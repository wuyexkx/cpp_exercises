cmake_minimum_required(VERSION 3.4.1)
# PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR

# 指定编译器路径
SET(CMAKE_C_COMPILER "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/gcc.exe")
SET(CMAKE_CXX_COMPILER "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/g++.exe")

# 添加完下面代码，自动生成demo_BINARY_DIR 和 demo_SOURCE_DIR
# Note: project must put after "SET(CMAKE_C_COMPILER)"
project(TM)

# 需要的源文件和头文件目录
aux_source_directory(./src SRC_LIST) # 搜索cpp  src/./TicketMachine.cpp
# add include files
include_directories(./src)

# 将对应源文件生成 TM库（默认静态库）
add_library(TM ${SRC_LIST})

# main可执行文件
add_executable(main main.cpp)
# 将TM库 链接到main可执行文件
target_link_libraries(main TM)

# ==================================Note:================================
# in windows, must use "=====cmake -G "Unix Makefiles" ../=====" before "cmake .."
