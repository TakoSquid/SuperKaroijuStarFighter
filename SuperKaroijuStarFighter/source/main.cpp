#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <3ds.h>
#include <m3dia.hpp>

int main()
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("Hello, world!\n");

    // Main loop
    while (aptMainLoop())
    {
        gspWaitForVBlank();
        gfxSwapBuffers();
        hidScanInput();

        // Your code goes here
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break; // break in order to return to hbmenu
    }

    gfxExit();
    return 0;
}
