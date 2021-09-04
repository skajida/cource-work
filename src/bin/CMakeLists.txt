cmake_minimum_required(VERSION 3.10)

add_executable(main main.cpp)

# target_link_options(main PRIVATE -pthread)

target_link_libraries(main entities_lib)
