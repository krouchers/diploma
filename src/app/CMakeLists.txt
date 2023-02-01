cmake_minimum_required(VERSION 3.20)

include(${PROJECT_SOURCE_DIR}/cmake/cmake_utils.cmake)

build_library_with_type(app STATIC ${MODULE_COMPILE_FLAGS})

target_sources(app PRIVATE 
    src/app.cpp)   

target_include_directories(app PUBLIC include)
target_link_libraries(app PRIVATE platform)
