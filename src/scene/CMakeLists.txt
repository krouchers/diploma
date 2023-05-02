include(cmake_utils)

set(src_files
    src/scene.cc
    src/renderer.cc
    src/item.cc
    src/pose.cc
)

build_library_with_type(scene SHARED "${MODULE_COMPILE_FLAGS}" "${src_files}")

target_link_libraries(scene PUBLIC geometry)

target_compile_definitions(scene PRIVATE "-DDLL_EXPORT")
set_target_properties(scene PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

target_include_directories(scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
