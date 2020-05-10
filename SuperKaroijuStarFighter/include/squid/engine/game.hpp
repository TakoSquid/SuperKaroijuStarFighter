#pragma once

#include <string>
#include <m3dia.hpp>
#include "squid/engine/window.hpp"
#include "squid/tools/print.hpp"

namespace squid
{
class Game
{
public:
    Game();

    void Update();
    void LateUpdate();
    void Draw();
    bool IsRunning();

    void CalculateDeltaTime();

private:
    m3d::Applet app;
    squid::Window win;
    m3d::Sprite spr;
    m3d::Clock clock;
    float deltaTime;
};

} // namespace squid