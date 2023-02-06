include(${PROJECT_SOURCE_DIR}/cmake/cmake_utils.cmake)

build_library_with_type(platform STATIC ${MODULE_COMPILE_FLAGS})

target_sources(platform PRIVATE 
   src/window.cpp)   

target_link_libraries(platform PRIVATE SDL2::SDL2-static)

target_include_directories(platform PUBLIC include)

