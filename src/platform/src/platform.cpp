#include "platform.hpp"
#include "window.hpp"
#include "graphic.hpp"

platform::platform() = default;

platform::~platform() = default;

void platform::render()
{
    poll_and_process_events();
    gl_->render();
}

void platform::create_window(glm::vec2 size, std::string name)
{
    window_ = std::make_shared<window>(name, size);
    gl_ = std::make_unique<graphic>(window_);
}

void platform::poll_and_process_events()
{
    for (auto event : window_.get()->poll_events())
    {
        switch (event)
        {
        case event::QUIT:
            should_quit_ = true;
            break;

        default:
            break;
        }
    }
}