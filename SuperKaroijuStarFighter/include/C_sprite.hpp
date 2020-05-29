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
        void setAllocator(SpriteAllocator *spriteAllocator);
        void setScale(m3d::Vector2f scale);
        void flipX(bool flipX);
        void flipY(bool flipY);

        m3d::Vector2f getSize();

    private:
        SpriteAllocator *m_SpriteAllocator;
        m3d::Sprite spr_;
        bool m_flipX;
        bool m_flipY;
    };
} // namespace squid