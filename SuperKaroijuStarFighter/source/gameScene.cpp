#include "gameScene.hpp"

namespace squid
{
SceneGame::SceneGame() : spr_{"romfs:/gfx/images.t3x", 0}
{
}

void SceneGame::OnCreate()
{
}

void SceneGame::OnDestroy()
{
}

void SceneGame::ProcessInput()
{
}

void SceneGame::Update(float deltaTime)
{
    const m3d::Vector2f &spritePos = m3d::Vector2f{spr_.getXPosition(), spr_.getYPosition()};
    const int moveSpeed = 100;

    int xMove = 0;
    if (m3d::buttons::buttonDown(m3d::buttons::Left))
    {
        xMove = -moveSpeed;
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

    float xFrameMove = xMove * deltaTime;
    float yFrameMove = yMove * deltaTime;

    spr_.setPosition(spritePos.u + xFrameMove, spritePos.v + yFrameMove);
}

void SceneGame::Draw(Window &window)
{
    window.Draw(spr_);
}
} // namespace squid