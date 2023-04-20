#pragma once
#include <iostream>
#include <memory>

#include "definitions.hpp"
#include "gui_interface.hpp"
#include "window_interface.hpp"

class Opengl;

class GEODIP_API DearGui : public IGui
{

public:
    DearGui(const std::shared_ptr<Opengl> &gl, const std::shared_ptr<IWindow> &window);
    void Render() final;
    void AddSlider(const std::string &name, float &value);

private:
    std::shared_ptr<IWindow> window_;
    std::shared_ptr<Opengl> gl_;
};