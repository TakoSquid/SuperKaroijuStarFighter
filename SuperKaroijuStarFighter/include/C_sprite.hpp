#pragma once

#include "squid/engine/component.hpp"
#include "squid/engine/spriteAllocator.hpp"

namespace squid
{
    class C_Sprite : public Component
    {
    public:
        C_Sprite(Object *owner);
        int classType() override;

        void Load(int id);

        void Start() override;
        void LateUpdate(float deltaTime) override;
        void Draw(Window &window) override;

        void setOpacity(float opacity);
        void setTint(m3d::Color tint);
        void setScale(m3d::Vector2f scale);
        void setCenter(m3d::Vector2f center);
        void flipX(bool flipX);
        void flipY(bool flipY);

        m3d::Vector2f getSize();

    private:
        m3d::Sprite spr_;
        m3d::Vector2f currentScale;
        m3d::Vector2f centerRel;
        bool needToBeUpdated;
    };
} // namespace squid