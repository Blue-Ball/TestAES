cmake_minimum_required(VERSION 3.10)
project(test_aes_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(${PROJECT_NAME} main.cpp include/aes.h include/aes.hpp include/aes.c)
