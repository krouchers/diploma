#pragma once

#include "math.hpp"

class IWindow
{
public:
    virtual float get_aspect_ratio() = 0;
    virtual void create_window(std::string const &window_name, vec2 const &size) = 0;
    virtual bool should_quit() = 0;
    virtual void *get_handler() = 0;
    virtual void close() = 0;
};
