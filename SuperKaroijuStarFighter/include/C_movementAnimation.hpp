#pragma once

#include <memory>

#include "component.hpp"
#include "C_velocity.hpp"
#include "C_animation.hpp"

namespace squid
{
    class C_MovementAnimation : public Component
    {
    public:
        int classType() override;

        C_MovementAnimation(Object *owner);

        void Awake() override;

        void Update(float deltaTime) override;

    private:
        std::shared_ptr<C_Velocity> velocity;
        std::shared_ptr<C_Animation> animation;
    };
} // namespace squid