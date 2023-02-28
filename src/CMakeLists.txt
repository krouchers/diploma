set(MODULES 
    utils
    platform
    app
    glad
    math)

set(MODULE_COMPILE_FLAGS "-Wall -Wextra -Werror -Wshadow")

foreach(MODULE ${MODULES})
    add_subdirectory(${MODULE})
endforeach()
