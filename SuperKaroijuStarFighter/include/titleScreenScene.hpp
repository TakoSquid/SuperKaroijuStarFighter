#pragma once

#include "squid/engine/scene.hpp"
#include "squid/engine/sceneStateMachine.hpp"
#include "squid/engine/spriteAllocator.hpp"
#include "squid/engine/objectCollection.hpp"
#include "C_scrollingBackground.hpp"
#include "C_sprite.hpp"
#include "C_followTrail.hpp"
#include "C_goTowards.hpp"
#include "C_offsetPad.hpp"
#include "C_blinking.hpp"

//test
#include "C_simpleController.hpp"

namespace squid
{
    class TitleScreenScene : public Scene
    {
    public:
        TitleScreenScene(SceneStateMachine &sceneStateMachine, SpriteAllocator &spriteAllocator);

        void SceneAfterStart(unsigned int id);

        void OnCreate() override;
        void OnDestroy() override;
        void OnActivate() override;
        void OnDeactivate() override;
        void Update(float deltaTime) override;
        void LateUpdate(float deltaTime) override;
        void Draw(Window &window) override;

    private:
        SceneStateMachine &m_sceneStateMachine;
        SpriteAllocator &m_spriteAllocator;
        unsigned int m_sceneAfterStart;

        ObjectCollection m_Objects;

        std::shared_ptr<squid::C_FollowTrail> karoFollowTrail;

        std::shared_ptr<squid::Object> titleObj;
        std::shared_ptr<squid::Object> pressStartObj;
        std::shared_ptr<squid::C_Blinking> pressStartBling;

        float m_fade;

        m3d::Music m_music;
        m3d::Sound m_sound;
    };
} // namespace squid