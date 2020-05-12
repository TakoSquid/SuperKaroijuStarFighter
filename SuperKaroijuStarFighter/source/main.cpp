#include <m3dia.hpp>
#include "squid.hpp"

int main()
{
    squid::Game game;

    consoleInit(GFX_BOTTOM, NULL);

    while (game.IsRunning())
    {
        game.Update();
        game.LateUpdate();
        squid::printAt(1, 1, "---DEBUG---");
        game.Draw();
        game.CalculateDeltaTime();
    }

    return 0;
}
