#pragma once
#include <iostream>
#include <memory>

#include "definitions.hpp"
#include "gui_interface.hpp"
#include "window_interface.hpp"

class opengl;
class sdl_window;

class GEODIP_API dear_gui : public IGui
{

public:
    dear_gui(const std::shared_ptr<opengl> &gl, const std::shared_ptr<IWindow> &window);
    void init() final;
    void render() final;
    void hello();

private:
    std::shared_ptr<opengl> gl_;
    std::shared_ptr<IWindow> window_;
};