#include "C_sprite.hpp"

#include "squid/engine/object.hpp"

#include "squid/tools/print.hpp"
#include <string>
#include <iostream>

namespace squid
{
    C_Sprite::C_Sprite(Object *owner)
        : Component(owner)
    {
    }

    int C_Sprite::classType()
    {
        return C_SPRITE;
    }

    void C_Sprite::Load(int id)
    {
        if (m_SpriteAllocator)
            spr_ = m_SpriteAllocator->getSprite(id);
    }

    void C_Sprite::Start()
    {
        spr_.setPosition(owner_->transform->GetPosition());
    }

    void C_Sprite::LateUpdate(float deltaTime)
    {
        spr_.setPosition(owner_->transform->GetPosition());
    }

    void C_Sprite::Draw(Window &window)
    {
        window.Draw(spr_);
    }

    void C_Sprite::setOpacity(float opacity)
    {
        spr_.setOpacity(255 * opacity);
    }

    void C_Sprite::setTint(m3d::Color tint)
    {
        spr_.setTint(tint);
        spr_.setBlend(tint.getAlpha() / 255.0f);
    }

    void C_Sprite::setAllocator(SpriteAllocator *spriteAllocator)
    {
        m_SpriteAllocator = spriteAllocator;
    }

    m3d::Vector2f C_Sprite::getSize()
    {
        return spr_.getSize();
    }

} // namespace squid