#pragma once

#include "squid/engine/scene.hpp"
#include "squid/engine/sceneStateMachine.hpp"
#include "squid/engine/objectCollection.hpp"
#include "C_scrollingBackground.hpp"
#include "C_sprite.hpp"

//test
#include "C_simpleController.hpp"

namespace squid
{
class TitleScreenScene : public Scene
{
public:
    TitleScreenScene(SceneStateMachine &sceneStateMachine);

    void SceneAfterStart(unsigned int id);

    void OnCreate() override;
    void OnDestroy() override;
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void Draw(Window &window) override;

private:
    SceneStateMachine m_sceneStateMachine;
    unsigned int m_sceneAfterStart;

    ObjectCollection m_Objects;
};
} // namespace squid