include(cmake_utils)

set(imgui_sources
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
)

# build_library_with_type(imgui STATIC "${MODULE_COMPILE_FLAGS}" "${imgui_sources}")

# target_link_libraries(imgui PRIVATE SDL2::SDL2)
# target_include_directories(imgui PUBLIC
#     ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)

set(src_files
    src/gui.cc
    src/editor.cc
)

build_library_with_type(dear_gui SHARED "${MODULE_COMPILE_FLAGS}" "${src_files};${imgui_sources}")
target_link_libraries(dear_gui PUBLIC IGui scene utils common)
target_link_libraries(dear_gui PRIVATE opengl)
target_include_directories(dear_gui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src/common
    PRIVATE ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
target_compile_definitions(dear_gui PRIVATE "-DDLL_EXPORT")
set_target_properties(dear_gui PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
