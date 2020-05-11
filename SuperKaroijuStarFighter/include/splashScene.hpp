#pragma once

#include "squid.hpp"

namespace squid
{
class SplashScene : public Scene
{
public:
    SplashScene(SceneStateMachine &sceneStateMachine);

    void OnCreate() override;
    void OnDestroy() override;

    void OnActivate() override;

    void SetSwitchToScene(unsigned int id);

    void Update(float deltaTime) override;
    void Draw(Window &window) override;

private:
    m3d::Sprite splashSprite_;
    SceneStateMachine &sceneStateMachine_;

    float showForSeconds_;

    float currentSeconds_;

    unsigned int switchToState_;
};
} // namespace squid