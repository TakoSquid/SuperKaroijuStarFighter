#include <m3dia.hpp>
#include "squid.hpp"

int main()
{
    m3d::Applet app;
    m3d::Screen scr;

    squid::Vector2f test = squid::Vector2f(45.0f, 20.0f);

    consoleInit(GFX_BOTTOM, NULL);

    while (app.isRunning())
    {
        squid::printAt(0, 0, std::to_string(app.getCurrentFrame()));
        squid::printAt(0, 1, std::to_string(test.x));
        std::cout << test << std::endl;
        scr.render();
    }

    return 0;
}
