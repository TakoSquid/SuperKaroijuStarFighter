#pragma once

#include "squid/engine/component.hpp"

namespace squid
{
    class C_Transform : public Component
    {
    public:
        C_Transform(Object *owner);
        int classType() override;

        void SetPosition(float x, float y);
        void SetPosition(const m3d::Vector2f &pos);

        void AddPosition(float x, float y);
        void AddPosition(m3d::Vector2f pos);

        void SetX(float x);
        void SetY(float y);

        void AddX(float x);
        void AddY(float y);

        void SetAngle(float a);
        void Rotate(float a);
        float GetAngle() const;

        void Draw(Window &window) override;

        const m3d::Vector2f &GetPosition() const;

        void SetStatic(bool isStatic);
        bool isStatic() const;

    private:
        m3d::Vector2f position_;
        float angle_;

        bool isStaticTransform;
    };
} // namespace squid