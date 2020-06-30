#include <m3dia.hpp>
#include "squid.hpp"
///////////////

int main()
{
    squid::Game game;

    consoleInit(GFX_BOTTOM, NULL);

    while (game.IsRunning())
    {
        consoleClear();

        game.Update();
        game.LateUpdate();
        game.Draw();
        game.CalculateDeltaTime();
    }

    return 0;
}
