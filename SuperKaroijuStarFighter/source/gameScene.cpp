#include "gameScene.hpp"

#include "C_simpleController.hpp"
#include "C_sprite.hpp"
#include "C_animation.hpp"
#include "C_scrollingBackground.hpp"

#include "tinyxml2.h"

namespace squid
{
    GameScene::GameScene(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocactor)
        : m_sceneStateMachine{sceneStateMachine},
          m_spriteAllocator{spriteAllocactor}, test("romfs:/gfx/forest.t3x"),
          mapParser(test)
    {
    }

    void GameScene::OnCreate()
    {

        std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse("romfs:/forest_map.xml", m3d::Vector2f{8.0f, 8.0f});

        for (auto &obj : levelTiles)
        {
            m_Objects.Add(obj);
        }

        auto player = std::make_shared<Object>();
        player->transform->SetPosition(30, 120);
        player->SetSortOrder(100);

        auto sprite = player->AddComponent<C_Sprite>();
        sprite->setAllocator(&m_spriteAllocator);
        sprite->Load(7);
        sprite->flipX(true);

        auto animation = player->AddComponent<C_Animation>();
        animation->setSprite(sprite);

        auto controller = player->AddComponent<C_SimpleController>();
        controller->setAnimation(animation);

        std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>();

        idleAnimation->AddFrame(6, 0.2f);
        idleAnimation->AddFrame(7, 0.2f);

        animation->AddAnimation(squid::AnimationState::Idle, idleAnimation);

        std::shared_ptr<Animation> slowAnimation = std::make_shared<Animation>();

        slowAnimation->AddFrame(8, 0.2f);
        slowAnimation->AddFrame(9, 0.2f);
        slowAnimation->AddFrame(10, 0.2f);

        animation->AddAnimation(squid::AnimationState::SlowFly, slowAnimation);

        auto bgObj = std::make_shared<Object>();
        bgObj->transform->SetPosition(200, 120);

        auto scrollCompo = bgObj->AddComponent<C_ScrollingBackground>();
        bgObj->SetSortOrder(-100);
        scrollCompo->setAllocator(&m_spriteAllocator);
        scrollCompo->SetSpeed(0.0f);
        scrollCompo->SetSpriteId(11);

        m_Objects.Add(player);
        m_Objects.Add(bgObj);
    }
    void GameScene::OnDestroy() {}

    void GameScene::OnActivate()
    {
        C2D_Fade(C2D_Color32(0, 0, 0, 0));
    }
    void GameScene::OnDeactivate() {}

    void GameScene::Update(float deltaTime)
    {
        m_Objects.ProcessRemovals();
        m_Objects.ProcessNewObjects();

        m_Objects.Update(deltaTime);
    }

    void GameScene::LateUpdate(float deltaTime)
    {
        m_Objects.LateUpdate(deltaTime);
    }
    void GameScene::Draw(Window &window)
    {
        std::cout << "Il y a : " << m_Objects.getNumberObjects() << " objets dans la scene." << std::endl;
        m_Objects.Draw(window);
    }
} // namespace squid