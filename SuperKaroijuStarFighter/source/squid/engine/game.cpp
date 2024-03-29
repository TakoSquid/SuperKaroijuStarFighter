#include "game.hpp"

namespace squid
{

    Game::Game()
        : win{true},
          spriteAllocator("romfs:/gfx/images.t3x")
    {

        // auto titleScreen = std::make_shared<TitleScreenScene>(sceneStateMachine, spriteAllocator);
        // unsigned int titleScreenID = sceneStateMachine.Add(titleScreen);

        // auto gameScene = std::make_shared<GameScene>(sceneStateMachine, spriteAllocator, win);
        // unsigned int gameID = sceneStateMachine.Add(gameScene);

        // titleScreen->SceneAfterStart(gameID);

        // sceneStateMachine.SwitchTo(gameID);

        auto miniGamePlayer = std::make_shared<MiniGamePlayer>(sceneStateMachine, spriteAllocator, win);
        auto miniGamePlayerId = sceneStateMachine.Add(miniGamePlayer);

        sceneStateMachine.SwitchTo(miniGamePlayerId);

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
        std::cout << 1.0 / deltaTime << std::endl;

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