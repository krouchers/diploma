#pragma once
#include <memory>
#include "platform.hpp"

class app
{
public:
    app();
    app(app &&);
    void run();

private:
    app(const app &) = delete;
    app &operator=(const app &) = delete;

    std::unique_ptr<platform> platform_;
};
