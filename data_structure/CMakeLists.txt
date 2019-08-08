cmake_minimum_required(VERSION 3.4.1)
add_compile_options(-std=c++11)
project(data_structure)

include_directories(./include)
aux_source_directory(./src SRC_LIST)

add_library(my_func ${SRC_LIST})
# add_executable(sequenceStack_main sequenceStack_main.cpp)
# target_link_libraries(sequenceStack_main my_func)
# add_executable(sequenceQueue_main sequenceQueue_main.cpp)
# target_link_libraries(sequenceQueue_main my_func)

# add_executable(sort sort.cpp)
# add_executable(search search.cpp)
# add_executable(recursion recursion.cpp)
# add_executable(Recursion_binarySearch Recursion_binarySearch.cpp)
# add_executable(permutation permutation.cpp)
# add_executable(removeDuplicates removeDuplicates.cpp)

# add_executable(list_basis list_basis.cpp)
# add_executable(list_classNesting list_classNesting.cpp)

add_executable(List_main List_main.cpp)
target_link_libraries(List_main my_func)
