set(MODULES
    utils
    opengl
    interfaces
    sdl_window
    app
    scene
    glad
    gui
    math)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(MODULE_COMPILE_FLAGS "/Wall")
else()
    set(MODULE_COMPILE_FLAGS "-Wall -Wextra -Werror -Wshadow")
endif()

foreach(MODULE ${MODULES})
    add_subdirectory(${MODULE})
endforeach()
