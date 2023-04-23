include(cmake_utils)

set(src_files
   src/opengl.cpp
   src/shader.cpp
   src/mesh.cc
   src/tex2D.cc
)

build_library_with_type(opengl STATIC "${MODULE_COMPILE_FLAGS}" "${src_files}")

target_link_libraries(opengl PUBLIC math glad sdl_window utils glm::glm)

target_include_directories(opengl PUBLIC include)
