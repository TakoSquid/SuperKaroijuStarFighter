#include "gameScene.hpp"

#include "C_simpleController.hpp"
#include "C_sprite.hpp"
#include "C_animation.hpp"
#include "C_scrollingBackground.hpp"
#include "C_boxCollider.hpp"

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

        // Player
        auto player = std::make_shared<Object>();
        player->transform->SetPosition(30, 100);
        player->SetSortOrder(1);

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

        auto collider = player->AddComponent<C_BoxCollider>();
        collider->SetCollidable(m3d::BoundingBox(0, 0, 20, 20));
        collider->SetLayer(CollisionLayer::Default);

        // Background
        auto bgObj = std::make_shared<Object>();
        bgObj->transform->SetPosition(200, 120);

        auto scrollCompo = bgObj->AddComponent<C_ScrollingBackground>();
        bgObj->SetSortOrder(-100);
        scrollCompo->setAllocator(&m_spriteAllocator);
        scrollCompo->SetSpeed(0.0f);
        scrollCompo->SetSpriteId(11);

        // Platforme
        auto platform = std::make_shared<Object>();
        platform->transform->SetPosition(128, 200);

        auto platcollider = platform->AddComponent<C_BoxCollider>();
        platcollider->SetCollidable(m3d::BoundingBox(0, 0, 16, 16));
        platcollider->SetLayer(CollisionLayer::Tile);

        platformGoTowards = platform->AddComponent<C_GoTowards>();
        platformGoTowards->setGoal(m3d::Vector2f{platform->transform->GetPosition().u, 72});
        platformGoTowards->setSpeed(100.0f);

        m_Objects.Add(platform);
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
        if (platformGoTowards->done())
        {

            float y = platformGoTowards->owner_->transform->GetPosition().v;

            if (y == 72)
                platformGoTowards->setGoal(m3d::Vector2f{platformGoTowards->owner_->transform->GetPosition().u, 190});

            if (y == 190)
                platformGoTowards->setGoal(m3d::Vector2f{platformGoTowards->owner_->transform->GetPosition().u, 72});
        }

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

        // Debug::Draw(window);
    }
} // namespace squid