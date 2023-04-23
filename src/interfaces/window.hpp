#pragma once
#include <optional>

#include "math.hpp"

class IWindow
{
public:
    virtual void Close() = 0;
    virtual float GetAspectRatio() = 0;
    virtual bool ShouldQuit() = 0;
    virtual void *GetHandler() = 0;
    virtual void SwapFrame() = 0;
    virtual Vec2 GetSize() = 0;
};
