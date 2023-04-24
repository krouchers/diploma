
set(math_sources
    src/mat4x4.cc
    src/vec2.cc
    src/vec3.cc
    src/vec4.cc
    src/transforms.cc
)
add_library(math STATIC "${math_sources}")

target_include_directories(math PUBLIC include)