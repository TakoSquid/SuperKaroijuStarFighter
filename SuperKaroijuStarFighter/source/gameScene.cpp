#include "gameScene.hpp"

#include "C_simpleController.hpp"
#include "C_sprite.hpp"
#include "C_animation.hpp"

#include "tinyxml2.h"

namespace squid
{
    GameScene::GameScene(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocactor)
        : m_sceneStateMachine{sceneStateMachine},
          m_spriteAllocator{spriteAllocactor}, test("romfs:/gfx/jungle.t3x"),
          mapParser(test)
    {
    }

    void GameScene::OnCreate()
    {

        std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse("romfs:/map.xml", m3d::Vector2f{16.0f, 16.0f});

        for (auto &obj : levelTiles)
        {
            m_Objects.Add(obj);
        }

        auto player = std::make_shared<Object>();
        player->transform->SetPosition(200, 120);
        player->SetSortOrder(100);

        auto sprite = player->AddComponent<C_Sprite>();
        sprite->setAllocator(&m_spriteAllocator);
        sprite->Load(10);
        sprite->flipX(true);

        auto animation = player->AddComponent<C_Animation>();
        animation->setSprite(sprite);

        auto controller = player->AddComponent<C_SimpleController>();
        controller->setAnimation(animation);

        std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>();

        idleAnimation->AddFrame(9, 0.2f);
        idleAnimation->AddFrame(10, 0.2f);

        animation->AddAnimation(squid::AnimationState::Idle, idleAnimation);

        std::shared_ptr<Animation> slowAnimation = std::make_shared<Animation>();

        slowAnimation->AddFrame(11, 0.2f);
        slowAnimation->AddFrame(12, 0.2f);
        slowAnimation->AddFrame(13, 0.2f);

        animation->AddAnimation(squid::AnimationState::SlowFly, slowAnimation);

        m_Objects.Add(player);
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