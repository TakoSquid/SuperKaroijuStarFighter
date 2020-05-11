#include "gameScene.hpp"

namespace squid
{
SceneGame::SceneGame(SceneStateMachine &sceneStateMachine)
    : sceneStateMachine_{sceneStateMachine}, switchToState_{0}
{
}

void SceneGame::OnCreate()
{
    player_ = std::make_shared<Object>();

    auto sprite = player_->AddComponent<C_Sprite>();
    sprite->Load(0);

    auto movement = player_->AddComponent<C_SimpleController>();
}

void SceneGame::OnDestroy()
{
}

void SceneGame::Update(float deltaTime)
{
    player_->Update(deltaTime);
}

void SceneGame::LateUpdate(float deltaTime)
{
    player_->LateUpdate(deltaTime);
}

void SceneGame::Draw(Window &window)
{
    player_->Draw(window);
}

void SceneGame::SetSwitchToScene(unsigned int id)
{
    switchToState_ = id;
}
} // namespace squid