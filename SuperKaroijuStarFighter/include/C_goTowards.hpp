#pragma once

#include <m3dia.hpp>
#include "squid/engine/component.hpp"

namespace squid
{
    class C_GoTowards : public Component
    {
    public:
        C_GoTowards(Object *owner);
        int classType() override;
        void setGoal(m3d::Vector2f goal);

        void Start() override;
        void setSpeed(float speed);
        void Update(float deltaTime) override;

        bool done() const;

    private:
        m3d::Vector2f m_goal;
        float m_speed;
        bool m_done;
        m3d::Vector2f calculatePlatformMovement(float deltaTime);
        float percentBetweenWayPoints;
        m3d::Vector2f from;
    };
} // namespace squid