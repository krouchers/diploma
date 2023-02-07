#include "platform.hpp"
#include "window.hpp"
#include "graphic.hpp"

platform::platform() = default;

platform::~platform() = default;

void platform::create_window(glm::vec2 size, std::string name)
{
    window_ = std::make_unique<window>(name);
    gl_ = std::make_unique<graphic>(*window_.get());
}