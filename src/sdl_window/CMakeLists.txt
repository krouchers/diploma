include(cmake_utils)

set(src_files src/sdl_window.cc)

build_library_with_type(sdl_window STATIC "${MODULE_COMPILE_FLAGS}" "${src_files}")

target_include_directories(sdl_window PUBLIC include ${PROJECT_SOURCE_DIR}/src/common)

# target_compile_definitions(sdl_window PRIVATE "-DDLL_EXPORT")

target_link_libraries(sdl_window PUBLIC utils IWindow SDL2::SDL2)

# set_target_properties(sdl_window PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)