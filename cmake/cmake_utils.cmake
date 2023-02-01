function(build_library_with_type name type cxx_flags)
    add_library(${name} ${type})
    set_target_properties(${name}
    PROPERTIES 
    COMPILE_FLAGS ${cxx_flags})
endfunction()
