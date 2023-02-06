#pragma once
#include <string>

#include "glm/vec2.hpp"

class window
{
public:
    window(std::string window_name, glm::vec2 size = {1280, 720});

private:
    glm::vec2 size_{1280, 720};
    std::string name_;
    void create_window();
};