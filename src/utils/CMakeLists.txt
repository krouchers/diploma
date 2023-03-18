include(${PROJECT_SOURCE_DIR}/cmake/cmake_utils.cmake)

set(src_files
    src/log.cpp
    src/stb_loader.cc
)

build_library_with_type(utils STATIC "${MODULE_COMPILE_FLAGS}" "${src_files}")

target_include_directories(utils PUBLIC include)