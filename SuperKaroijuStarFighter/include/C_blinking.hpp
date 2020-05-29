#pragma once

#include "squid/engine/component.hpp"
#include "squid/engine/object.hpp"
#include "C_sprite.hpp"

namespace squid
{
    class C_Blinking : public Component
    {
    public:
        C_Blinking(Object *owner);

        int classType();

        void Awake() override;
        void Update(float deltaTime) override;

        void setTimeGoal(float time);

    private:
        std::shared_ptr<C_Sprite> m_sprite;
        float m_timer;
        float m_timeGoal;
        bool m_toggle;
    };
} // namespace squid