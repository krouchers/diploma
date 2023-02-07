#include "graphic.hpp"
#include "window.hpp"
#include "log.hpp"

graphic::graphic(const window &win)
{
    info("Creating GL context\n");
    SDL_GL_CreateContext(win.get_sdl_handler());
}

graphic::~graphic()
{
    info("Destroing GL context\n");
    SDL_GL_DeleteContext(gl_context_);
}