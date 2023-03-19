cmake_minimum_required(VERSION 3.24)
project(TESTING)

set(CMAKE_CXX_STANDARD 17)

add_executable(TESTING main.cpp Questions.hpp Test.hpp User.hpp)
