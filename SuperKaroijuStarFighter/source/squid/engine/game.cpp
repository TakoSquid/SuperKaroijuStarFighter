#include "game.hpp"

namespace squid
{

    Game::Game()
        : win{true}
    {
        auto titleScreen = std::make_shared<TitleScreenScene>(sceneStateMachine, spriteAllocator);
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
        std::cout << "current scene : " << sceneStateMachine.getCurrentSceneId() << std::endl;
        std::cout << "sprite allocator loaded : " << spriteAllocator.nLoadedSprites() << std::endl;

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