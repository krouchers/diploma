include(${PROJECT_SOURCE_DIR}/cmake/cmake_utils.cmake)

set(src_files  
   src/window.cpp
   src/platform.cpp
   src/graphic.cpp
   src/shader.cpp
)   

build_library_with_type(platform STATIC ${MODULE_COMPILE_FLAGS} "${src_files}")

target_link_libraries(platform PRIVATE SDL2-static utils glad)
target_link_libraries(platform PUBLIC glm)

target_include_directories(platform PUBLIC include)

