#include <iostream>

#include "window.hpp"
#include "app.hpp"

void print(int a)
{
    std::cout << a << '\n';
}

app::app()
    : window_{new window{"test window"}}
{
}

app::~app()
{
    delete window_;
}
