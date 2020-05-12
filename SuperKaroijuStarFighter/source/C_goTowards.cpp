#include "C_goTowards.hpp"

#include "squid/engine/object.hpp"
#include "squid/tools/vector.hpp"

namespace squid
{
C_GoTowards::C_GoTowards(Object *owner)
    : Component(owner),
      m_goal{0, 0},
      m_speed{100.0f},
      m_done{true}
{
}

int C_GoTowards::classType()
{
    return C_GOTOWARDS;
}

void C_GoTowards::setGoal(m3d::Vector2f goal)
{
    m_goal = goal;
    m_done = false;
}

void C_GoTowards::setSpeed(float speed)
{
    m_speed = speed;
}
void C_GoTowards::Start()
{
    //m_goal = owner_->transform->GetPosition();
}

void C_GoTowards::Update(float deltaTime)
{
    if (!m_done)
    {
        m3d::Vector2f direction = (m_goal - owner_->transform->GetPosition()).normalize() * m_speed * deltaTime;

        if ((owner_->transform->GetPosition() - m_goal).sqrMagnitude() <= 1 || is_between(owner_->transform->GetPosition(), m_goal, owner_->transform->GetPosition() + direction))
        {
            owner_->transform->SetPosition(m_goal);
            m_done = true;
        }
        else
        {
            owner_->transform->AddPosition(direction);
        }
    }
}

} // namespace squid