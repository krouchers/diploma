#include "platform.hpp"
#include "window.hpp"
#include "graphic.hpp"

platform::platform() = default;

platform::~platform() = default;

void platform::render()
{
    while (!should_close_window())
    {
        
        gl_.get()->render();
    }
}

void platform::create_window(glm::vec2 size, std::string name)
{
    window_ = std::make_unique<window>(name);
    gl_ = std::make_unique<graphic>(*window_.get());
    key_baf_ = SDL_GetKeyboardState(nullptr);
}

bool platform::should_close_window()
{
}