cmake_minimum_required(VERSION 3.16)
project(torch_cpp)

set(CMAKE_CXX_STANDARD 20)

include(cmake/CPM.cmake)
include(cmake/utilities.cmake)
include(cmake/LibTorch.cmake)

install_liborch_mac(1.5.0)

add_subdirectory(basics)
