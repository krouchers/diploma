include(cmake_utils)

set(src_files
    src/scene.cc
    src/renderer.cc
    src/item.cc
)

build_library_with_type(scene STATIC "${MODULE_COMPILE_FLAGS}" "${src_files}")

target_link_libraries(scene PUBLIC opengl dear_gui)

target_include_directories(scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
