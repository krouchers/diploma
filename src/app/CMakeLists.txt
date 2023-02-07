cmake_minimum_required(VERSION 3.20)

include(${PROJECT_SOURCE_DIR}/cmake/cmake_utils.cmake)

add_executable(test-bed 
    src/main.cpp
    src/app.cpp
)

target_link_libraries(test-bed PRIVATE platform)
target_include_directories(test-bed PRIVATE include)

set_target_properties(test-bed PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

