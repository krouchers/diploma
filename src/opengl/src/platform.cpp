#include "platform.hpp"
#include "window.hpp"
#include "opengl.hpp"
#include "SDL.h"

#include <cstring>

namespace
{
    SDL_Scancode get_sdl_key_code(keys key)
    {
        switch (key)
        {
        case keys::LEFT:
            return SDL_SCANCODE_RIGHT;
        case keys::RIGHT:
            return SDL_SCANCODE_LEFT;
        default:
            return SDL_SCANCODE_UNKNOWN;
        }
    }
}

platform::platform() : m_key_buf_current{SDL_GetKeyboardState(nullptr)}
{
}

platform::~platform() = default;

void platform::render()
{
    poll_and_process_events();
    gl_->render();
}

void platform::create_window(glm::vec2 size, std::string name, camera const &cam)
{
    window_ = std::make_shared<IWindow>(name, size);
}

void platform::poll_and_process_events()
{
    std::memcpy(m_key_buf_previous, m_key_buf_current, 512 * sizeof(m_key_buf_current[0]));
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                should_quit_ = true;
                break;
            default:
                break;
            }
        }
    }
}

bool platform::is_pressed(keys key)
{
    auto sdl_code{get_sdl_key_code(key)};
    return m_key_buf_current[sdl_code] && (m_key_buf_previous[sdl_code] == 0);
}