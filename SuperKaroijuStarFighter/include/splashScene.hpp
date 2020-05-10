#pragma once

#include "squid/engine/scene.hpp"
#include "squid/engine/sceneStateMachine.hpp"
#include "squid/engine/window.hpp"

namespace squid
{
class SplashScene : public Scene
{
public:
    SplashScene(SceneStateMachine &sceneStateMachine, Window &window);

    void OnCreate() override;
    void OnDestroy() override;

    void OnActivate() override;

    void SetSwitchToScene(unsigned int id);

    void Update(float deltaTime) override;
    void Draw(Window &window) override;

private:
    m3d::Sprite splashSprite_;
    SceneStateMachine &sceneStateMachine_;
    Window &window_;

    float showForSeconds_;

    float currentSeconds_;

    unsigned int switchToState_;
};
} // namespace squid