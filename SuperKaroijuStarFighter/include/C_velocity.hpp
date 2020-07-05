#pragma once

#include <algorithm>
#include "component.hpp"
#include <m3dia.hpp>

namespace squid
{
    class C_Velocity : public Component
    {
    public:
        int classType() override;

        C_Velocity(Object *owner);

        void Update(float deltaTime) override;
        void Set(const m3d::Vector2f &vel);
        void Set(float x, float y);
        const m3d::Vector2f &Get() const;

    private:
        void ClampVelocity();

        m3d::Vector2f velocity;
        m3d::Vector2f maxVelocity;
    };
} // namespace squid