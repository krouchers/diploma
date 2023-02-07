include(${PROJECT_SOURCE_DIR}/cmake/cmake_utils.cmake)

build_library_with_type(platform STATIC ${MODULE_COMPILE_FLAGS})

target_sources(platform PRIVATE 
   src/window.cpp
   src/platform.cpp
   src/graphic.cpp)   

target_link_libraries(platform PRIVATE SDL2-static utils)
target_link_libraries(platform PUBLIC glm)

target_include_directories(platform PUBLIC include)

