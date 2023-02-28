#include <iostream>

#include "app.hpp"
#include "math.hpp"

int main()
{
    try
    {
        app application{};
        application.run();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}