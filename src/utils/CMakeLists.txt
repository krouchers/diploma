include(${PROJECT_SOURCE_DIR}/cmake/cmake_utils.cmake)

set(src_files
    src/log.cpp
    src/stb_loader.cc
    src/camera.cc
    src/generate_primitives.cc
)

build_library_with_type(utils STATIC "${MODULE_COMPILE_FLAGS}" "${src_files}")

target_link_libraries(utils PUBLIC math glm::glm geometry)

target_include_directories(utils PUBLIC include)