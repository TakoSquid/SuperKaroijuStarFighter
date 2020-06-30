#include "gameScene.hpp"

#include "C_simpleController.hpp"
#include "C_sprite.hpp"
#include "C_animation.hpp"
#include "C_scrollingBackground.hpp"
#include "C_boxCollider.hpp"

#include "tinyxml2.h"

// 192.168.137.157 23/06/2020
// 192.168.137.146

namespace squid
{
    GameScene::GameScene(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocactor)
        : m_sceneStateMachine{sceneStateMachine},
          m_spriteAllocator{spriteAllocactor}, test("romfs:/gfx/jungle.t3x"),
          mapParser(test)
    {
        cam = m_Objects.getCamera();
    }

    void GameScene::OnCreate()
    {

        std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse("romfs:/map.xml", m3d::Vector2f{16.0f, 16.0f});

        for (auto &obj : levelTiles)
        {
            m_Objects.Add(obj);
        }

        // Player
        player = std::make_shared<Object>();
        player->transform->SetPosition(30, 100);
        player->SetSortOrder(1000);

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
        collider->SetLayer(CollisionLayer::Player);

        // Background
        auto bgObj = std::make_shared<Object>();
        bgObj->SetSortOrder(-100);
        bgObj->transform->SetPosition(200, 120);

        auto bgSpr = bgObj->AddComponent<C_Sprite>();
        bgSpr->setAllocator(&m_spriteAllocator);
        bgSpr->Load(11);

        // Platforme
        auto platform = std::make_shared<Object>();
        platform->transform->SetPosition(128, 200);
        platform->SetSortOrder(500);

        auto platcollider = platform->AddComponent<C_BoxCollider>();
        platcollider->SetCollidable(m3d::BoundingBox(0, 0, 16, 16));
        platcollider->SetLayer(CollisionLayer::Tile);

        platformGoTowards = platform->AddComponent<C_GoTowards>();
        platformGoTowards->setGoal(m3d::Vector2f{platform->transform->GetPosition().u, 72});
        platformGoTowards->setSpeed(100.0f);

        auto platformSprite = platform->AddComponent<C_Sprite>();
        platformSprite->setAllocator(&m_spriteAllocator);
        platformSprite->Load(12);

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

        const float smol = 0.01f;

        if (cam)
        {

            float X = cos(cam->getAngle());
            float Y = sin(cam->getAngle());

            std::cout << cam->getAngle() << std::endl;

            if (m3d::buttons::buttonDown(m3d::buttons::X))
            {
                cam->scaling(smol * 3);
            }

            if (m3d::buttons::buttonDown(m3d::buttons::Y))
            {
                cam->scaling(-smol * 3);
            }

            if (m3d::buttons::buttonDown(m3d::buttons::A))
            {
                cam->rotate(smol * 10);
            }

            if (m3d::buttons::buttonDown(m3d::buttons::B))
            {
                cam->rotate(-smol * 10);
            }

            if (m3d::buttons::buttonDown(m3d::buttons::DPadRight))
            {
                cam->translate(-X, Y);
            }

            if (m3d::buttons::buttonDown(m3d::buttons::DPadLeft))
            {
                cam->translate(X, -Y);
            }

            if (m3d::buttons::buttonDown(m3d::buttons::DPadUp))
            {
                cam->translate(Y, X);
            }

            if (m3d::buttons::buttonDown(m3d::buttons::DPadDown))
            {
                cam->translate(-Y, -X);
            }

            auto pos = player->transform->GetPosition();
            X = pos.u;
            Y = pos.v;

            cam->setPosition(-X, -Y);
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
    }
} // namespace squid