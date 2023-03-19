#pragma once
#include <memory>

class platform;

class app
{
public:
    app();
    app(app &&);
    void run();

    ~app();

private:
    app(const app &) = delete;
    app &operator=(const app &) = delete;

    std::unique_ptr<platform> platform_;
};
