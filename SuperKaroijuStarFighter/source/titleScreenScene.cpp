#include "titleScreenScene.hpp"

#include "squid/tools/color.hpp"

namespace squid
{
TitleScreenScene::TitleScreenScene(SceneStateMachine &sceneStateMachine)
    : m_sceneStateMachine{sceneStateMachine},
      m_sceneAfterStart{0},
      m_music("romfs:/bgm.mp3")
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
    karoObj->transform->SetPosition(0, 120);
    auto trail = karoObj->AddComponent<C_FollowTrail>();

    //Title
    auto titleObj = std::make_shared<Object>();
    auto titleSprite = titleObj->AddComponent<C_Sprite>();
    titleSprite->Load(0);
    auto towards = titleObj->AddComponent<C_GoTowards>();
    towards->setGoal(m3d::Vector2f{270, 130});
    titleObj->transform->SetPosition(270, -titleSprite->getSize().v / 2.0f);

    //Adding all objs
    m_Objects.Add(bgObj);
    m_Objects.Add(titleObj);
    m_Objects.Add(karoObj);

    m_music.loop(true);
}

void TitleScreenScene::OnDestroy()
{
}

void TitleScreenScene::OnActivate()
{
    m_music.play();
}

void TitleScreenScene::OnDeactivate()
{
    m_music.stop();
}

void TitleScreenScene::Update(float deltaTime)
{
    m_Objects.ProcessRemovals();
    m_Objects.ProcessNewObjects();

    if (m3d::buttons::buttonPressed(m3d::buttons::B))
    {
        m_sceneStateMachine.SwitchTo(m_sceneAfterStart);
    }

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