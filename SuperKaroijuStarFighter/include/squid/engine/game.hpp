#pragma once

#include <string>
#include <m3dia.hpp>
#include "squid/engine/window.hpp"
#include "squid/tools/print.hpp"
#include "squid/engine/sceneStateMachine.hpp"
#include "splashScene.hpp"
#include "gameScene.hpp"
#include "titleScreenScene.hpp"

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
    m3d::Clock clock;
    float deltaTime;

    SceneStateMachine sceneStateMachine;
};

} // namespace squid