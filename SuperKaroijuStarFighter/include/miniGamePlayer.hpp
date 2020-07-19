#pragma once

#include "squid/engine/scene.hpp"
#include "squid/engine/sceneStateMachine.hpp"
#include "squid/engine/spriteAllocator.hpp"
#include "squid/engine/objectCollection.hpp"

#include "miniGame.hpp"
#include "C_sprite.hpp"

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
        ObjectCollection miniGameObjects;

        std::shared_ptr<Object> rope;
        std::shared_ptr<C_Sprite> tv_screen_spr;

        float zoomProgress;
        bool zoomDirection;

        std::vector<MiniGame> miniGamePool;
        MiniGame *currentMiniGame;

        void updateZoomProgress(float deltaTime);
        void setMiniGame(unsigned int index);
    };
} // namespace squid