#pragma once

#include "squid/engine/component.hpp"
#include "C_animation.hpp"

namespace squid
{
    class C_SimpleController : public Component
    {
    public:
        C_SimpleController(Object *owner);
        int classType() override;

        void SetMovementSpeed(int moveSpeed);

        void Awake() override;
        void Update(float deltaTime) override;

    private:
        int moveSpeed;
        std::shared_ptr<C_Animation> animation;
    };
} // namespace squid