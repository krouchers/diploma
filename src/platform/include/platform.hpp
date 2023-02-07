#pragma once

#include <memory>
#include <string>

#include "glm/vec2.hpp"

class window;
class graphic;

class platform
{
public:
    void create_window(glm::vec2 size, std::string name);
    platform();
    ~platform();

private:
    std::unique_ptr<window> window_;
    std::unique_ptr<graphic> gl_;
};