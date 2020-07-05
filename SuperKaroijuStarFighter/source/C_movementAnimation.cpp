#include "C_movementAnimation.hpp"
#include "object.hpp"

namespace squid
{
    int C_MovementAnimation::classType()
    {
        return C_MOVEMENTANIMATION;
    }

    C_MovementAnimation::C_MovementAnimation(Object *owner)
        : Component(owner)
    {
    }

    void C_MovementAnimation::Awake()
    {
        velocity = owner_->GetComponent<C_Velocity>();
        animation = owner_->GetComponent<C_Animation>();
    }

    void C_MovementAnimation::Update(float deltaTime)
    {
        if (animation->GetAnimationState() != AnimationState::Casting)
        {
            const m3d::Vector2f &currentVel = velocity->Get();

            if ((currentVel.u != 0) | (currentVel.v != 0))
            {
                animation->SetAnimationState(AnimationState::SlowFly);
            }
            else
            {
                animation->SetAnimationState(AnimationState::Idle);
            }
        }
    }
} // namespace squid