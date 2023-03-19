#include "platform.hpp"
#include "app.hpp"
#include "log.hpp"

app::app()
    : platform_{new platform{}}
{
    platform_->create_window({1280, 720}, "my window");
}

app::~app() = default;

void app::run()
{
    while (!platform_->should_quit())
    {
        platform_->render();
        if (platform_->is_pressed(keys::LEFT))
        {
            info("Key %d is pressed", keys::LEFT);
        }

        if (platform_->is_pressed(keys::RIGHT))
        {
            info("Key %d is pressed", keys::RIGHT);
        }
    }
}
