#pragma once

#include <memory>
#include <m3dia.hpp>

#include "squid/engine/component.hpp"
#include "squid/engine/animation.hpp"
#include "C_velocity.hpp"

namespace squid
{
    class C_Direction : public Component
    {
    public:
        int classType() override;

        C_Direction(Object *owner);

        void Awake() override;
        FacingDirection Get();

    private:
        std::shared_ptr<C_Velocity> velocity;
        FacingDirection currentDir;
    };
} // namespace squid