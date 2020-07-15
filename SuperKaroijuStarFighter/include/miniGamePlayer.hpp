#pragma once

#include "squid/engine/scene.hpp"
#include "squid/engine/sceneStateMachine.hpp"
#include "squid/engine/spriteAllocator.hpp"
#include "squid/engine/objectCollection.hpp"

namespace squid
{
    class MiniGamePlayer : public Scene
    {
    public:
        MiniGamePlayer(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocactor, Window &window);

        void OnCreate() override;
        void OnDestroy() override;

        void OnActivate() override;
        void OnDeactivate() override;

        void Update(float deltaTime) override;
        void LateUpdate(float deltaTime) override;
        void Draw(Window &window);

    private:
        SceneStateMachine &m_sceneStateMachine;
        SpriteAllocator &m_spriteAllocator;
        Window &m_window;
        SharedContext context;

        ObjectCollection m_objects;
    };
} // namespace squid