#include "miniGamePlayer.hpp"

#include "squid/tools/tools.hpp"

#include "C_sprite.hpp"
#include "C_boxCollider.hpp"
#include "C_velocity.hpp"
#include "C_simpleController.hpp"

namespace squid
{
    MiniGamePlayer::MiniGamePlayer(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocator, Window &window)
        : m_sceneStateMachine(sceneStateMachine),
          m_spriteAllocator(spriteAllocator),
          m_window(window),
          context{&m_objects, &m_spriteAllocator, &m_window}
    {
    }

    void MiniGamePlayer::OnCreate()
    {
        // auto tv_screen = std::make_shared<Object>(&context);
        // auto tv_screen_spr = tv_screen->AddComponent<C_Sprite>();
        // tv_screen_spr->Load(0);

        // m_objects.Add(tv_screen);

        auto obstacle = std::make_shared<Object>(&context);
        obstacle->transform->SetStatic(true);
        auto obstacleCollider = obstacle->AddComponent<C_BoxCollider>();
        obstacleCollider->SetCollidable(m3d::BoundingBox{0, 0, 20, 20});

        m_objects.Add(obstacle);

        auto player = std::make_shared<Object>(&context);
        player->transform->SetPosition(m3d::Vector2f{20, 120});
        auto playerCollider = player->AddComponent<C_BoxCollider>();
        playerCollider->SetCollidable(m3d::BoundingBox{0, 0, 20, 20});
        player->AddComponent<C_Velocity>();
        player->AddComponent<C_SimpleController>();

        m_objects.Add(player);
    }

    void MiniGamePlayer::OnDestroy()
    {
    }

    void MiniGamePlayer::OnActivate()
    {
    }
    void MiniGamePlayer::OnDeactivate()
    {
    }

    void MiniGamePlayer::Update(float deltaTime)
    {
        // static float t = 0.0f;
        // static float sens = 1.0f;

        // auto cam = m_objects.getCamera();
        // cam->setPosition(lerp(m3d::Vector2f{-200.0f, -120.0f}, m3d::Vector2f{-182.0f, -120.0f}, t));
        // cam->setScale(lerp(1.0f, 1.5f, t));

        // std::cout << t << std::endl;
        // t = std::clamp(t + deltaTime * sens * 4.0f, 0.0f, 1.0f);

        // if (m3d::buttons::buttonPressed(m3d::buttons::A))
        // {
        //     sens *= -1.0f;
        // }

        m_objects.ProcessRemovals();
        m_objects.ProcessNewObjects();

        m_objects.Update(deltaTime);
    }

    void MiniGamePlayer::LateUpdate(float deltaTime)
    {
        m_objects.LateUpdate(deltaTime);
    }

    void MiniGamePlayer::Draw(Window &window)
    {
        m_objects.Draw(window);
    }
} // namespace squid