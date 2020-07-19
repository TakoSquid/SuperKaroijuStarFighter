#include "miniGamePlayer.hpp"

#include "squid/tools/tools.hpp"

#include "C_boxCollider.hpp"
#include "C_velocity.hpp"
#include "C_simpleController.hpp"
#include "C_removeObjectOnCollisionEnter.hpp"
#include "C_goTowards.hpp"

#include "minigames/dodge.hpp"

namespace squid
{
    MiniGamePlayer::MiniGamePlayer(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocator, Window &window)
        : m_sceneStateMachine(sceneStateMachine),
          m_spriteAllocator(spriteAllocator),
          m_window(window),
          context{&m_objects, &m_spriteAllocator, &m_window},
          zoomProgress{0.0f},
          zoomDirection{false}
    {
    }

    void MiniGamePlayer::OnCreate()
    {
        // auto missingTextutre = std::make_shared<Object>(&context);
        // missingTextutre->SetSortOrder(-100);
        // auto missingTexture_spr = missingTextutre->AddComponent<C_Sprite>();
        // missingTexture_spr->Load(2);

        // m_objects.Add(missingTextutre);

        auto tv_screen = std::make_shared<Object>(&context);
        tv_screen->SetSortOrder(10);
        tv_screen_spr = tv_screen->AddComponent<C_Sprite>();
        tv_screen_spr->Load(0);

        m_objects.Add(tv_screen);

        rope = std::make_shared<Object>(&context);
        rope->SetSortOrder(9);
        auto rope_spr = rope->AddComponent<C_Sprite>();
        rope_spr->Load(1);
        rope_spr->setCenter(m3d::Vector2f{0.0f, 0.5f});
        rope->transform->SetPosition(0.0f, 190.0f);
        auto go = rope->AddComponent<C_GoTowards>();

        m_objects.Add(rope);

        Dodge dodge = Dodge(&context, 0);

        miniGamePool.push_back(dodge);

        for (auto &obj : dodge.getObjects())
        {
            miniGameObjects.Add(obj);
        }
        // setMiniGame(0);
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
        auto cam = m_objects.getCamera();
        cam->setPosition(lerp(m3d::Vector2f{-200.0f, -120.0f}, m3d::Vector2f{-182.0f, -120.0f}, zoomProgress));
        cam->setScale(lerp(1.0f, 1.5f, zoomProgress));

        tv_screen_spr->setOpacity(lerp(0.0f, 1.0f, 1.0f - zoomProgress));

        static float timer = 5.0f;
        std::cout << timer << std::endl;

        static auto done = false;

        if (!done)
        {
            auto go = rope->GetComponent<C_GoTowards>();
            auto spr = rope->GetComponent<C_Sprite>();
            go->setGoal(m3d::Vector2f{-spr->getSize().u, rope->transform->GetPosition().v});
            go->setSpeed(spr->getSize().u / 5.0f);
            done = true;
        }

        timer = std::clamp(timer - deltaTime, 0.0f, 5.0f);

        if (m3d::buttons::buttonPressed(m3d::buttons::A))
        {
            zoomDirection = !zoomDirection;
        }

        updateZoomProgress(deltaTime);

        m_objects.ProcessRemovals();
        m_objects.ProcessNewObjects();
        m_objects.Update(deltaTime);

        miniGameObjects.ProcessRemovals();
        miniGameObjects.ProcessNewObjects();

        if (zoomProgress != 0)
            miniGameObjects.Update(deltaTime);
    }

    void MiniGamePlayer::LateUpdate(float deltaTime)
    {
        m_objects.LateUpdate(deltaTime);
        if (zoomProgress != 0)
            miniGameObjects.LateUpdate(deltaTime);
    }

    void MiniGamePlayer::Draw(Window &window)
    {
        m_objects.Draw(window);
        miniGameObjects.Draw(window);
    }

    void MiniGamePlayer::updateZoomProgress(float deltaTime)
    {
        std::cout << zoomProgress << std::endl;

        auto sens = 1.0f;

        if (!zoomDirection)
            sens = -1.0f;
        ;

        zoomProgress = std::clamp(zoomProgress + deltaTime * sens * 4.0f, 0.0f, 1.0f);
    }

    void MiniGamePlayer::setMiniGame(unsigned int index)
    {
        miniGameObjects.QueueEveryObjects();
        miniGameObjects.ProcessRemovals();

        currentMiniGame = &miniGamePool.at(index % miniGamePool.size());

        for (auto &obj : currentMiniGame->getObjects())
        {
            miniGameObjects.Add(obj);
        }
    }
} // namespace squid