set(MODULES
    utils
    opengl
    interfaces
    sdl_window
    app
    scene
    glad
    geometry
    gui
    math)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(MODULE_COMPILE_FLAGS "/Wall")
else()
    set(MODULE_COMPILE_FLAGS "-Wall -Wextra -Werror -Wshadow")
endif()
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")

foreach(MODULE ${MODULES})
    add_subdirectory(${MODULE})
endforeach()
