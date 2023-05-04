include(cmake_utils)

set(src_files
   src/opengl.cpp
   src/shader.cpp
   src/tex2D.cc
   src/lines.cc
   src/framebuffer.cc
   src/effects.cc
)

build_library_with_type(opengl STATIC "${MODULE_COMPILE_FLAGS}" "${src_files}")

target_link_libraries(opengl PUBLIC math glad sdl_window utils glm::glm common)

target_include_directories(opengl PUBLIC include)
