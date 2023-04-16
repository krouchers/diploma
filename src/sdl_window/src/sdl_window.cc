#include "window/sdl_window.hpp"

void sdl_window::create_window(std::string const &window_name, vec2 const &size)
{
    m_size = size;
    info("Initializing SDL");
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        throw std::runtime_error("Failed to init sdl");
    }

    info("Creating window");
    m_sdl_handler = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                     size.x, size.y, SDL_WINDOW_OPENGL);
    if (!m_sdl_handler)
    {
        throw std::runtime_error("Failed to create window");
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
}

float sdl_window::get_aspect_ratio()
{
    return m_size.y / m_size.x;
}

bool sdl_window::should_quit()
{
    SDL_Event e;
    bool should_quit{false};
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                should_quit = true;
                break;
            default:
                break;
            }
        }
    }
    return should_quit;
}

void *sdl_window::get_handler()
{
    return m_sdl_handler;
}