# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/cmake-3.15.0-rc3-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /usr/cmake-3.15.0-rc3-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wuyexkx/cpp/cpp_exercises/class_constructor_copy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wuyexkx/cpp/cpp_exercises/class_constructor_copy/build

# Include any dependencies generated for this target.
include CMakeFiles/my_func.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/my_func.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_func.dir/flags.make

CMakeFiles/my_func.dir/src/operator_overloading.cpp.o: CMakeFiles/my_func.dir/flags.make
CMakeFiles/my_func.dir/src/operator_overloading.cpp.o: ../src/operator_overloading.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wuyexkx/cpp/cpp_exercises/class_constructor_copy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_func.dir/src/operator_overloading.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_func.dir/src/operator_overloading.cpp.o -c /home/wuyexkx/cpp/cpp_exercises/class_constructor_copy/src/operator_overloading.cpp

CMakeFiles/my_func.dir/src/operator_overloading.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_func.dir/src/operator_overloading.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wuyexkx/cpp/cpp_exercises/class_constructor_copy/src/operator_overloading.cpp > CMakeFiles/my_func.dir/src/operator_overloading.cpp.i

CMakeFiles/my_func.dir/src/operator_overloading.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_func.dir/src/operator_overloading.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wuyexkx/cpp/cpp_exercises/class_constructor_copy/src/operator_overloading.cpp -o CMakeFiles/my_func.dir/src/operator_overloading.cpp.s

# Object files for target my_func
my_func_OBJECTS = \
"CMakeFiles/my_func.dir/src/operator_overloading.cpp.o"

# External object files for target my_func
my_func_EXTERNAL_OBJECTS =

libmy_func.a: CMakeFiles/my_func.dir/src/operator_overloading.cpp.o
libmy_func.a: CMakeFiles/my_func.dir/build.make
libmy_func.a: CMakeFiles/my_func.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wuyexkx/cpp/cpp_exercises/class_constructor_copy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmy_func.a"
	$(CMAKE_COMMAND) -P CMakeFiles/my_func.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_func.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_func.dir/build: libmy_func.a

.PHONY : CMakeFiles/my_func.dir/build

CMakeFiles/my_func.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_func.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_func.dir/clean

CMakeFiles/my_func.dir/depend:
	cd /home/wuyexkx/cpp/cpp_exercises/class_constructor_copy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wuyexkx/cpp/cpp_exercises/class_constructor_copy /home/wuyexkx/cpp/cpp_exercises/class_constructor_copy /home/wuyexkx/cpp/cpp_exercises/class_constructor_copy/build /home/wuyexkx/cpp/cpp_exercises/class_constructor_copy/build /home/wuyexkx/cpp/cpp_exercises/class_constructor_copy/build/CMakeFiles/my_func.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_func.dir/depend

