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
    inline bool should_quit() { return should_quit_; }

private:
    void poll_and_process_events();

    std::shared_ptr<window> window_;
    std::unique_ptr<graphic> gl_;
    bool should_quit_{false};

    /**
     * @brief Буффер, хранящий текущее состояние клавиатуры. 
     * 
     */
    const uint8_t *m_key_buf;
};