cmake_minimum_required(VERSION 3.4.1)
add_compile_options(-std=c++11)
project(basicSkill2)


aux_source_directory(./src SRC_LIST)
include_directories(./include)

# add_library(my_func ${SRC_LIST})

# add_executable(conversionFunction conversionFunction.cpp)
# target_link_libraries(singleton my_func)

# add_executable(pointer_like_class pointer_like_class.cpp)

# add_executable(function_like_class function_like_class.cpp)

# add_executable(specialization specialization.cpp)

# add_executable(partial_specialization partial_specialization.cpp)

# add_executable(template_template_parameter template_template_parameter.cpp)

# add_executable(variadic_templates variadic_templates.cpp)

# add_executable(auto_use auto_use.cpp)

# add_executable(for_use for_use.cpp)

add_executable(single_list single_list.cpp)

