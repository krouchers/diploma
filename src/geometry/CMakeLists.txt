include(cmake_utils)

set(src_files
    src/mesh.cc
)

build_library_with_type(geometry STATIC "$MODULE_COMPILE_FLAGS" "${src_files}")
target_link_libraries(geometry PUBLIC opengl)
target_include_directories(geometry PUBLIC include)