#include <iostream>

#include "app.hpp"
#include "math.hpp"

int main(int argc, char *argv[])
{
    try
    {
        App application{};
        application.Run();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }

    return 0;
}