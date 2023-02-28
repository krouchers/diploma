cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

project(test-bed LANGUAGES CXX)

# Adding dependencies
include(cmake/deps.cmake)

add_subdirectory(src)

