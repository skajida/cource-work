cmake_minimum_required(VERSION 3.5)

project(course-work)

set(CMAKE_CXX_STANDART 20)

add_definitions(-O2 -Wall)

if (UNIX)
    add_definitions(-Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default
                    -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op
                    -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor
                    -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual -Wsign-promo
                    -Weffc++)
elseif (WIN32)
    # add_definitions()
endif()

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(bin)
add_subdirectory(implementation)
