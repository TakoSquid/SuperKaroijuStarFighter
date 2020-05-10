#include "game.hpp"

namespace squid
{

Game::Game()
    : win{false}, spr{"romfs:/gfx/images.t3x", 0}
{
    clock.start();
    deltaTime = clock.getTime().getAsSeconds();
}

void Game::Update()
{
    if (m3d::buttons::buttonDown(m3d::buttons::Start) && m3d::buttons::buttonDown(m3d::buttons::Select))
        app.exit();

    win.Update();

    const m3d::Vector2f &spritePos = m3d::Vector2f{spr.getXPosition(), spr.getYPosition()};
    const int moveSpeed = 100.0f;

    int xMove = 0;
    if (m3d::buttons::buttonDown(m3d::buttons::Left)) // 1
    {
        xMove = -moveSpeed; // 2
    }
    else if (m3d::buttons::buttonDown(m3d::buttons::Right))
    {
        xMove = moveSpeed;
    }

    int yMove = 0;
    if (m3d::buttons::buttonDown(m3d::buttons::Up))
    {
        yMove = -moveSpeed;
    }
    else if (m3d::buttons::buttonDown(m3d::buttons::Down))
    {
        yMove = moveSpeed;
    }

    float xFrameMove = xMove * deltaTime; // 2
    float yFrameMove = yMove * deltaTime;

    spr.setPosition(spritePos.u + xFrameMove, spritePos.v + yFrameMove);
}

void Game::LateUpdate()
{
}

void Game::Draw()
{
    win.BeginDraw();
    win.Draw(spr);
    printAt(0, 0, std::to_string(deltaTime));
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