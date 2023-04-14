include(cmake_utils)

set(src_files  
   src/window.cpp
   src/platform.cpp
   src/graphic.cpp
   src/shader.cpp
   src/mesh.cc
   src/tex2D.cc
)   

build_library_with_type(platform STATIC ${MODULE_COMPILE_FLAGS} "${src_files}")

target_link_libraries(platform PRIVATE SDL2-static utils glad math)
target_link_libraries(platform PUBLIC glm)

target_include_directories(platform PUBLIC include)

