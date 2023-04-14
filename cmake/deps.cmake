include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.26.2
)

FetchContent_Declare(
    GLM 
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG efec5db081e3aad807d0731e172ac597f6a39447
)

FetchContent_Declare(
    IMGUI 
    GIT_REPOSITORY https://github.com/ocornut/imgui 
    GIT_TAG v1.89.4 
)

FetchContent_MakeAvailable(
    SDL3 GLM IMGUI
)