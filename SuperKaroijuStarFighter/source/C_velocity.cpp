#include "C_velocity.hpp"

#include "Object.hpp"

namespace squid
{
    int C_Velocity::classType()
    {
        return C_VELOCITY;
    }

    C_Velocity::C_Velocity(Object *owner)
        : Component(owner),
          maxVelocity{500.0f, 500.0f}
    {
    }

    void C_Velocity::Update(float deltaTime)
    {
        owner_->transform->AddPosition(velocity * deltaTime);
    }

    void C_Velocity::Set(const m3d::Vector2f &vel)
    {
        velocity = vel;
        ClampVelocity();
    }

    void C_Velocity::Set(float x, float y)
    {
        Set(m3d::Vector2f{x, y});
    }

    const m3d::Vector2f &C_Velocity::Get() const
    {
        return velocity;
    }

    void C_Velocity::ClampVelocity()
    {
        velocity.u = std::clamp<float>(velocity.u, -maxVelocity.u, maxVelocity.u);
        velocity.v = std::clamp<float>(velocity.v, -maxVelocity.v, maxVelocity.v);
    }

} // namespace squid