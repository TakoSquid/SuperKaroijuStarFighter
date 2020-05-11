#include "gameScene.hpp"

namespace squid
{
SceneGame::SceneGame(SceneStateMachine &sceneStateMachine)
    : sceneStateMachine_{sceneStateMachine}, switchToState_{0}
{
}

void SceneGame::OnCreate()
{
    auto player = std::make_shared<Object>();

    auto sprite = player->AddComponent<C_Sprite>();
    sprite->Load(0);

    auto movement = player->AddComponent<C_SimpleController>();

    objects_.Add(player);
}

void SceneGame::OnDestroy()
{
}

void SceneGame::Update(float deltaTime)
{
    objects_.ProcessRemovals();
    objects_.ProcessNewObjects();

    objects_.Update(deltaTime);
}

void SceneGame::LateUpdate(float deltaTime)
{
    objects_.LateUpdate(deltaTime);
}

void SceneGame::Draw(Window &window)
{
    objects_.Draw(window);
}

void SceneGame::SetSwitchToScene(unsigned int id)
{
    switchToState_ = id;
}
} // namespace squid