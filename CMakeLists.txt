cmake_minimum_required(VERSION 3.25)

project(test-bed LANGUAGES CXX)

add_subdirectory(src)

add_executable(test-bed src/main.cpp)

target_link_libraries(test-bed PRIVATE app)

set_target_properties(test-bed PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
