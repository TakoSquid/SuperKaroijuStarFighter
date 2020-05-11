#include "game.hpp"

namespace squid
{

Game::Game()
    : win{true}
{

    /*std::shared_ptr<SplashScene> splashScreen = std::make_shared<SplashScene>(sceneStateMachine);
    std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>(sceneStateMachine);

    unsigned int splashScreenID = sceneStateMachine.Add(splashScreen);
    unsigned int gameSceneID = sceneStateMachine.Add(gameScene);

    splashScreen->SetSwitchToScene(gameSceneID);
    gameScene->SetSwitchToScene(splashScreenID);*/

    auto titleScreen = std::make_shared<TitleScreenScene>(sceneStateMachine);
    unsigned int titleScreenID = sceneStateMachine.Add(titleScreen);

    titleScreen->SceneAfterStart(titleScreenID);

    sceneStateMachine.SwitchTo(titleScreenID);

    clock.start();
    deltaTime = clock.getTime().getAsSeconds();
}

void Game::Update()
{
    if (m3d::buttons::buttonDown(m3d::buttons::Start) && m3d::buttons::buttonDown(m3d::buttons::Select))
        app.exit();

    win.Update();

    sceneStateMachine.Update(deltaTime);
}

void Game::LateUpdate()
{
    sceneStateMachine.LateUpdate(deltaTime);
}

void Game::Draw()
{
    win.BeginDraw();

    sceneStateMachine.Draw(win);

    win.EndDraw();
}

bool Game::IsRunning()
{
    return app.isRunning();
}

void Game::CalculateDeltaTime()
{
    deltaTime = clock.getTime().getAsSeconds();
    clock.reset();
}
} // namespace squid