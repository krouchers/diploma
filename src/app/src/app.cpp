#include "platform.hpp"
#include "app.hpp"

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
    }
}
