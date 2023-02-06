#pragma once
#include <string>

class window
{
public:
    window(std::string window_name);

private:
    std::string name_;
    void create_window();
};