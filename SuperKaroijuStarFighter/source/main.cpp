#include <iostream>
#include <m3dia.hpp>

int main()
{
    m3d::Applet app;
    m3d::Screen scr;

    consoleInit(GFX_BOTTOM, NULL);

    while (app.isRunning())
    {
        scr.render();
    }

    return 0;
}
