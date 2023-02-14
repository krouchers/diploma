function(build_library_with_type name type cxx_flags src)
    add_library(${name} ${type} ${src})
    set_target_properties(${name}
    PROPERTIES 
    COMPILE_FLAGS ${cxx_flags})
endfunction()

function(list_include_directories target)
    get_target_property(DIRS ${target} INTERFACE_INCLUDE_DIRECTORIES) 
    foreach(DIR ${DIRS})
        message(STATUS ${DIR}) 
    endforeach()
endfunction()

