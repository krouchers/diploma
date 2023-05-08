#pragma once

#include "interfaces/event.hpp"
#include "scene/scene.hpp"

class IGui
{
public:
    virtual void Render3D(Scene &) = 0;
    virtual void RenderUi() = 0;
    virtual void ProcessEvent(const Event &) = 0;
    virtual void Drag() = 0;
};