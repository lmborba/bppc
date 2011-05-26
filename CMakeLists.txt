cmake_minimum_required(VERSION 2.8)

project(bppc)

add_executable(bppc bpp.cpp bppc.cpp incidence.cpp graph.cpp main.cpp)

include(UseDoxygen OPTIONAL)