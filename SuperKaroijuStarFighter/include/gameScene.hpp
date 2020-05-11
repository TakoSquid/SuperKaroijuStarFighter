#pragma once

#include "squid.hpp"
#include "C_sprite.hpp"
#include "C_simpleController.hpp"
#include "object.hpp"
#include "objectCollection.hpp"

namespace squid
{
class SceneGame : public Scene
{
public:
    SceneGame(SceneStateMachine &sceneStateMachine);

    void OnCreate() override;
    void OnDestroy() override;

    void Update(float deltaTime) override;
    void Draw(Window &window) override;
    void LateUpdate(float deltaTime) override;

    void SetSwitchToScene(unsigned int id);

private:
    SceneStateMachine &sceneStateMachine_;
    unsigned int switchToState_;

    ObjectCollection objects_;
};
} // namespace squid