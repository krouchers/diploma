set(MODULES 
    utils
    platform
    app)

set(MODULE_COMPILE_FLAGS -Wall -Wextra -Werr)

foreach(MODULE ${MODULES})
    add_subdirectory(${MODULE})
endforeach()
