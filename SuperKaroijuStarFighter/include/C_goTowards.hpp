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

private:
    m3d::Vector2f m_goal;
    float m_speed;
    bool m_done;
};
} // namespace squid