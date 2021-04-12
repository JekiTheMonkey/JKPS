#include "../Headers/Application.hpp"
#include "../Headers/Settings.hpp"

#include <stdexcept>
#include <iostream>

int main()
{
    Settings settings("KPS.cfg");
    Application app(settings);
    
    try
    {
        app.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}