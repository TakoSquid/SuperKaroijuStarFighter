#include "gameScene.hpp"

#include "C_simpleController.hpp"
#include "C_sprite.hpp"
#include "C_animation.hpp"
#include "C_scrollingBackground.hpp"
#include "C_boxCollider.hpp"
#include "C_projectileAttack.hpp"
#include "C_velocity.hpp"
#include "C_movementAnimation.hpp"
#include "C_goTowards.hpp"
#include "C_direction.hpp"

#include "tinyxml2.h"

// 192.168.137.157 23/06/2020
// 192.168.137.146

namespace squid
{
    GameScene::GameScene(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocactor, Window &window)
        : m_sceneStateMachine{sceneStateMachine},
          m_spriteAllocator{spriteAllocactor}, test("romfs:/gfx/jungle.t3x"),
          window(window),
          context{&m_Objects, &m_spriteAllocator, &window},
          tilesContext{context},
          mapParser(tilesContext)
    {
        cam = m_Objects.getCamera();
    }

    void GameScene::OnCreate()
    {
        tilesContext = context;
        tilesContext.spriteAllocator = &test;

        std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse("romfs:/map.xml", m3d::Vector2f{16.0f, 16.0f});

        for (auto &obj : levelTiles)
        {
            context.objects->Add(obj);
        }

        // Player
        player = std::make_shared<Object>(&context);
        player->transform->SetPosition(30, 100);
        player->SetSortOrder(1000);

        auto sprite = player->AddComponent<C_Sprite>();
        sprite->Load(7);
        sprite->flipX(true);

        player->AddComponent<C_Velocity>();
        player->AddComponent<C_Direction>();
        player->AddComponent<C_SimpleController>();

        auto collider = player->AddComponent<C_BoxCollider>();
        collider->SetCollidable(m3d::BoundingBox(0, 0, 20, 20));
        collider->SetLayer(CollisionLayer::Player);

        auto animation = player->AddComponent<C_Animation>();
        player->AddComponent<C_ProjectileAttack>();
        player->AddComponent<C_MovementAnimation>();

        std::map<FacingDirection, std::shared_ptr<Animation>> idleAnimations;
        std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>();
        idleAnimation->AddFrame(6, 0.2f);
        idleAnimation->AddFrame(7, 0.2f);
        idleAnimations.insert(std::make_pair(FacingDirection::None, idleAnimation));
        animation->AddAnimation(AnimationState::Idle, idleAnimations);

        std::map<FacingDirection, std::shared_ptr<Animation>> slowAnimations;
        std::shared_ptr<Animation> slowAnimation = std::make_shared<Animation>();
        slowAnimation->AddFrame(8, 0.2f);
        slowAnimation->AddFrame(9, 0.2f);
        slowAnimation->AddFrame(10, 0.2f);
        slowAnimations.insert(std::make_pair(FacingDirection::None, slowAnimation));
        animation->AddAnimation(AnimationState::SlowFly, slowAnimations);

        std::map<FacingDirection, std::shared_ptr<Animation>> spellAnimations;
        std::shared_ptr<Animation> spellAnimation = std::make_shared<Animation>();
        spellAnimation->AddFrame(13, 0.2f);
        spellAnimation->AddFrame(14, 0.2f);
        spellAnimation->AddFrame(15, 0.2f);
        spellAnimations.insert(std::make_pair(FacingDirection::None, spellAnimation));
        animation->AddAnimation(AnimationState::Casting, spellAnimations);

        // // Background
        auto bgObj = std::make_shared<Object>(&context);
        bgObj->SetSortOrder(-100);
        bgObj->transform->SetPosition(200, 120);

        auto bgSpr = bgObj->AddComponent<C_Sprite>();
        bgSpr->Load(11);

        // Platforme
        auto platform = std::make_shared<Object>(&context);
        platform->transform->SetPosition(128, 200);
        platform->SetSortOrder(500);

        auto platcollider = platform->AddComponent<C_BoxCollider>();
        platcollider->SetCollidable(m3d::BoundingBox(0, 0, 16, 16));
        platcollider->SetLayer(CollisionLayer::Tile);

        auto platformGoTowards = platform->AddComponent<C_GoTowards>();
        platformGoTowards->setGoal(m3d::Vector2f{platform->transform->GetPosition().u, 72});
        platformGoTowards->setSpeed(100.0f);

        auto platformSprite = platform->AddComponent<C_Sprite>();
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

        auto pPos = player->transform->GetPosition();

        // cam->setPosition(-pPos.u, -pPos.v);

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
        std::cout << context.spriteAllocator->nLoadedSprites() << std::endl;

        std::cout << "Il y a : " << m_Objects.getNumberObjects() << " objets dans la scene." << std::endl;

        m_Objects.Draw(window);
    }
} // namespace squid