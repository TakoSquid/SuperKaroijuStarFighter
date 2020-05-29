#pragma once

#include <m3dia.hpp>
#include "squid/engine/object.hpp"
#include "squid/engine/component.hpp"

namespace squid
{

    class C_OffsetPad : public Component
    {
    public:
        C_OffsetPad(Object *owner);

        void Start() override;
        void LateUpdate(float deltaTime) override;

        int classType() override;

        void setMagnitude(float magnitude);

    private:
        m3d::Vector2f offset;
        float m_magnitude;
    };

} // namespace squid