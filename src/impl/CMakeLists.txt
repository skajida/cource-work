cmake_minimum_required(VERSION 3.10)

file(GLOB CXX_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_library(entities_lib ${CXX_SOURCES})
