cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

project(test-bed LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(MY_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH ${MY_MODULE_PATH})

option(BUILD_TESTS "Whether build tests" OFF)

# Adding dependencies
include(deps)

add_subdirectory(src)

message(STATUS "Build tests: ${BUILD_TESTS}")

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()


