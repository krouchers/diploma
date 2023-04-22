#pragma once
#include <iostream>
#include <memory>

#include "definitions.hpp"
#include "interfaces/gui.hpp"
#include "interfaces/window.hpp"

class Opengl;

class GEODIP_API DearGui : public IGui
{

public:
    DearGui(const std::shared_ptr<Opengl> &gl,
            const std::shared_ptr<IWindow> &window);
    void Render() final;
    void AddSlider(const std::string &name, float &value);
    void ProcessEvent(const Event &) final;

private:
    std::shared_ptr<IWindow> window_;
    std::shared_ptr<Opengl> gl_;
};