#pragma once

#include "squid/engine/scene.hpp"

namespace squid
{
class SceneGame : public Scene
{
public:
    SceneGame();

    void OnCreate() override;
    void OnDestroy() override;

    void ProcessInput() override;
    void Update(float deltaTime) override;
    void Draw(Window &window) override;

private:
    m3d::Sprite spr_;
};
} // namespace squid