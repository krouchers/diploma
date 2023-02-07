#include "platform.hpp"
#include "app.hpp"

app::app()
    : platform_{new platform{}}
{
    platform_->create_window({1280, 720}, "my window");
}

void app::run(){

}
