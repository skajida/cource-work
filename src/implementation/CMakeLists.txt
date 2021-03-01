cmake_minimum_required(VERSION 3.13)

file(GLOB CXX_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_library(entities_lib ${CXX_SOURCES})
