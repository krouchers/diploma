#include <iostream>

#include "app.hpp"

int main(int argc, char **argv)
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