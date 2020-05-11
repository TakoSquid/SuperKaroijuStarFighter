#include "splashScene.hpp"

namespace squid
{
SplashScene::SplashScene(SceneStateMachine &sceneStateMachine)
    : splashSprite_{"romfs:/gfx/images.t3x", 0}, sceneStateMachine_{sceneStateMachine}, showForSeconds_{4.0f}, currentSeconds_{0.0f}, switchToState_{0}
{
}

void SplashScene::OnCreate()
{
    splashSprite_.setPosition(200, 120);
}

void SplashScene::OnActivate()
{
    currentSeconds_ = 0.f;
}

void SplashScene::OnDestroy() {}

void SplashScene::SetSwitchToScene(unsigned int id)
{
    switchToState_ = id;
}

void SplashScene::Update(float deltaTime)
{
    currentSeconds_ += deltaTime;

    if (currentSeconds_ >= showForSeconds_)
    {
        // Switches states.
        sceneStateMachine_.SwitchTo(switchToState_);
    }
}

void SplashScene::Draw(Window &window)
{
    window.Draw(splashSprite_);
}

} // namespace squid