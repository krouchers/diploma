cmake_minimum_required(VERSION 3.20)

include(cmake_utils)

add_executable(test-bed 
    src/main.cpp
    src/app.cpp
)

target_link_libraries(test-bed PRIVATE platform math utils)
target_include_directories(test-bed PRIVATE include)

install(TARGETS test-bed)

# set_target_properties(test-bed PROPERTIES
# RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

