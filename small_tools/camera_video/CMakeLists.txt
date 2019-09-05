cmake_minimum_required(VERSION 3.4.1)
# PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR

# 指定编译器路径
SET(CMAKE_C_COMPILER "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/gcc.exe")
SET(CMAKE_CXX_COMPILER "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/g++.exe")

# 添加完下面代码，自动生成demo_BINARY_DIR 和 demo_SOURCE_DIR
# Note: project must put after "SET(CMAKE_C_COMPILER)"
project(camera_video)

include_directories(C:/OpenCV-MinGW-Build-OpenCV-3.4.1-x64/include)
link_directories(C:/OpenCV-MinGW-Build-OpenCV-3.4.1-x64/x64/mingw/lib)  
add_executable(main main.cpp)  
# 去opencv编译代码中找到以下对应的.dll文件，然后复制到可执行文件.exe同路径下
# target_link_libraries(main libopencv_videoio341.dll libopencv_core341.dll libopencv_highgui341.dll libopencv_imgproc341.dll)  

# ==================================Note:================================
# in windows, must use "=====cmake -G "Unix Makefiles" ../=====" before "cmake .."

