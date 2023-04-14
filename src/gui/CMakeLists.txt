include(cmake/utils.cmake)

set(src_files
    src/gui.cc
)

build_library_with_type(dear_gui SHARED "${MODULE_COMPILE_FLAGS}" "${src_files}")
target_link_libraries(dear_gui PRIVATE )


