set(MODULES
    utils
    opengl
    interfaces
    sdl_window
    app
    glad
    math)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(MODULE_COMPILE_FLAGS "/Wall")
elseif()
    set(MODULE_COMPILE_FLAGS "-Wall -Wextra -Werror -Wshadow")
endif()

foreach(MODULE ${MODULES})
    add_subdirectory(${MODULE})
endforeach()
