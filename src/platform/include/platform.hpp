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

    void render();
private:
    std::unique_ptr<window> window_;
    std::unique_ptr<graphic> gl_;
    const uint8_t *key_baf_;
};