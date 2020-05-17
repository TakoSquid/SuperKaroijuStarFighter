#include "titleScreenScene.hpp"

#include "squid/tools/color.hpp"

namespace squid
{
    TitleScreenScene::TitleScreenScene(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocator)
        : m_sceneStateMachine{sceneStateMachine},
          m_spriteAllocator{spriteAllocator},
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
        spriteCompo->setAllocator(&m_spriteAllocator);
        spriteCompo->Load(7);

        auto scrollCompo = bgObj->AddComponent<C_ScrollingBackground>();
        scrollCompo->setAllocator(&m_spriteAllocator);
        scrollCompo->SetSpeed(200.0f);

        //Karo Géante
        auto karoObj = std::make_shared<Object>();
        karoObj->transform->SetPosition(75, 120);

        karoFollowTrail = karoObj->AddComponent<C_FollowTrail>();
        karoFollowTrail->setAllocator(&m_spriteAllocator);

        //Title
        titleObj = std::make_shared<Object>();

        auto titleSprite = titleObj->AddComponent<C_Sprite>();
        titleSprite->setAllocator(&m_spriteAllocator);
        titleSprite->Load(0);

        auto titleGoTowards = titleObj->AddComponent<C_GoTowards>();

        //Adding all objs

        m_Objects.Add(bgObj);
        m_Objects.Add(titleObj);
        m_Objects.Add(karoObj);
    }

    void TitleScreenScene::OnDestroy()
    {
    }

    void TitleScreenScene::OnActivate()
    {
        karoFollowTrail->Load(1);

        titleObj->transform->SetPosition(270, -titleObj->GetComponent<C_Sprite>()->getSize().v / 2.0f);
        titleObj->GetComponent<C_GoTowards>()->setGoal(m3d::Vector2f{270, 140});
        titleObj->GetComponent<C_GoTowards>()->setSpeed(250.0f);
    }

    void TitleScreenScene::OnDeactivate()
    {
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