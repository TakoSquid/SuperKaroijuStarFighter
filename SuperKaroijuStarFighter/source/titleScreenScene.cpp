#include "titleScreenScene.hpp"

#include "squid/tools/color.hpp"

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
    m_karoSprite = karoObj->AddComponent<C_Sprite>();
    m_karoSprite->Load(1);

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

    static float time = 0;

    time += deltaTime / 2.0f;
    m3d::Color c = rainbow(time);
    c.setAlpha(255.0f * 0.75f);

    m_karoSprite->setTint(c);
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