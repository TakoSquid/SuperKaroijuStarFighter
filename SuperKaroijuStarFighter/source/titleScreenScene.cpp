#include "titleScreenScene.hpp"

namespace squid
{
TitleScreenScene::TitleScreenScene(SceneStateMachine &sceneStateMachine)
    : m_sceneStateMachine{sceneStateMachine},
      m_sceneAfterStart{0}
{
}

void TitleScreenScene::SceneAfterStart(unsigned int id)
{
    m_sceneAfterStart = id;
}

void TitleScreenScene::OnCreate()
{
    //Background
    auto bgObj = std::make_shared<Object>();
    bgObj->transform->SetPosition(200, 120);

    auto spriteCompo = bgObj->AddComponent<C_Sprite>();
    spriteCompo->Load(7);

    auto scrollCompo = bgObj->AddComponent<C_ScrollingBackground>();
    scrollCompo->SetSpeed(200.0f);

    //Karo Géante
    auto karoObj = std::make_shared<Object>();
    auto sprite = karoObj->AddComponent<C_Sprite>();
    sprite->Load(1);

    //Adding all objs
    m_Objects.Add(bgObj);
    m_Objects.Add(karoObj);
}

void TitleScreenScene::OnDestroy()
{
}

void TitleScreenScene::Update(float deltaTime)
{
    m_Objects.ProcessRemovals();
    m_Objects.ProcessNewObjects();

    m_Objects.Update(deltaTime);
}

void TitleScreenScene::LateUpdate(float deltaTime)
{
    m_Objects.LateUpdate(deltaTime);
}

void TitleScreenScene::Draw(Window &window)
{
    m_Objects.Draw(window);
}
} // namespace squid