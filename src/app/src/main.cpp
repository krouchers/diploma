#include<iostream>

#include "app.hpp"

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