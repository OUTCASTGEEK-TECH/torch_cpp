cmake_minimum_required(VERSION 3.16)
project(basics)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/libtorch/share/cmake/Torch)
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(tensors tensors/tensors.cpp)
target_link_libraries(tensors "${TORCH_LIBRARIES}")

add_executable(tensors_arithmetics tensors/tensor_arithmetic.cpp)
target_link_libraries(tensors_arithmetics "${TORCH_LIBRARIES}")

add_executable(automatic_differenciation tensors/automatic_differenciation.cpp)
target_link_libraries(automatic_differenciation "${TORCH_LIBRARIES}")

add_executable(neural_network tensors/neural_network.cpp)
target_link_libraries(neural_network "${TORCH_LIBRARIES}")
