cmake_minimum_required(VERSION 3.10)

project(course-work)

set(CMAKE_CXX_STANDARD 17)

# target_compile_definitions
add_definitions(-O2 -Wall)

if (UNIX)
    add_definitions(
        -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal
        -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op
        -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor -Wstrict-null-sentinel
        -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++
    )
elseif (WIN32)
    #
endif()

add_subdirectory(bin)
add_subdirectory(impl)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(entities_lib PRIVATE ${CMAKE_SOURCE_DIR})
