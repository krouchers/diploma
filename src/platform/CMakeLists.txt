include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.26.2
)

FetchContent_MakeAvailable(
    SDL3
)

include(${PROJECT_SOURCE_DIR}/cmake/cmake_utils.cmake)

build_library_with_type(platform STATIC ${MODULE_COMPILE_FLAGS})

target_sources(platform PRIVATE 
   src/window.cpp)   

target_link_libraries(platform PRIVATE SDL2-static)

target_include_directories(platform PUBLIC include)

