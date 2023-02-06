#pragma once
#include <memory>

class window;
class app
{
public:
    app();
    app(app &&);
    ~app();

private:
    app(const app &) = delete;
    app &operator=(const app &) = delete;

    window *window_;
};
void print(int);
void call_window();
