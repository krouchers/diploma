#pragma once

#include "interfaces/event.hpp"

class IGui
{
public:
    virtual void Render() = 0;
    virtual void ProcessEvent(const Event &) = 0;
};