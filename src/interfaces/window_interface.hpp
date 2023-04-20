#pragma once

#include "math.hpp"

class IWindow
{
public:
    virtual float GetAspectRatio() = 0;
    virtual void CreateWindow(std::string const &window_name, Vec2 const &size) = 0;
    virtual bool ShouldQuit() = 0;
    virtual void *GetHandler() = 0;
};
