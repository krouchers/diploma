#include <iostream>

#include "app/app.hpp"

int main(int, char **argv)
{
    try
    {
        App application{argv[0]};
        application.Run();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }

    return 0;
}