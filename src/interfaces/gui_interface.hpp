#pragma once

class IGui
{
public:
    virtual void init() = 0;
    virtual void render() = 0;
};