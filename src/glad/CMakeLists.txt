include(${PROJECT_SOURCE_DIR}/cmake/cmake_utils.cmake)

build_library_with_type(glad SHARED "${MODULE_COMPILE_FLAGS}" src/glad.cpp)

target_compile_definitions(glad PRIVATE GLAD_GLAPI_EXPORT GLAD_GLAPI_EXPORT_BUILD)
target_compile_definitions(glad INTERFACE GLAD_GLAPI_EXPORT)

target_include_directories(glad PUBLIC include)

set_target_properties(glad PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
