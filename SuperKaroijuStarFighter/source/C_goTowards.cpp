#include "C_goTowards.hpp"

#include "squid/engine/object.hpp"
#include "squid/tools/vector.hpp"

namespace squid
{
    C_GoTowards::C_GoTowards(Object *owner)
        : Component(owner),
          m_goal{0, 0},
          m_speed{100.0f},
          m_done{true},
          percentBetweenWayPoints{0.0f},
          from{owner->transform->GetPosition()}
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
        from = owner_->transform->GetPosition();
        percentBetweenWayPoints = 0.0f;
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
            // m3d::Vector2f direction = (m_goal - owner_->transform->GetPosition()).normalize() * m_speed * deltaTime;

            // if ((owner_->transform->GetPosition() - m_goal).sqrMagnitude() <= 1 || is_between(owner_->transform->GetPosition(), m_goal, owner_->transform->GetPosition() + direction))
            // {
            //     owner_->transform->SetPosition(m_goal);
            //     m_done = true;
            // }
            // else
            // {
            //     owner_->transform->AddPosition(direction);
            // }

            m3d::Vector2f vel = calculatePlatformMovement(deltaTime);
            owner_->transform->AddPosition(vel);
        }
    }

    bool C_GoTowards::done() const
    {
        return m_done;
    }

    m3d::Vector2f C_GoTowards::calculatePlatformMovement(float deltaTime)
    {
        float distanceBetweenWaypoints = (from - m_goal).magnitude();
        percentBetweenWayPoints += deltaTime * m_speed / distanceBetweenWaypoints;
        percentBetweenWayPoints = std::clamp(percentBetweenWayPoints, 0.0f, 1.0f);

        auto t = percentBetweenWayPoints;

        if (percentBetweenWayPoints >= 1.0f)
        {
            m_done = true;
            owner_->transform->SetPosition(m_goal);
            return m3d::Vector2f{0, 0};
        }

        m3d::Vector2f newPos{m_goal.u * t + from.u * (1.0f - t), m_goal.v * t + from.v * (1.0f - t)};

        return newPos - owner_->transform->GetPosition();
    }

} // namespace squid