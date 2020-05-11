#include "C_sprite.hpp"

#include "squid/engine/object.hpp"

#include "squid/tools/print.hpp"
#include <string>
#include <iostream>

namespace squid
{
C_Sprite::C_Sprite(Object *owner)
    : Component(owner), spr_{"romfs:/gfx/images.t3x", 0}
{
    spr_.setPosition(owner_->transform->GetPosition());
}

int C_Sprite::classType()
{
    return C_SPRITE;
}

void C_Sprite::Load(int id)
{
    spr_ = m3d::Sprite{"romfs:/gfx/images.t3x", id};
    spr_.setCenterRel(0.5f, 0.5f);
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

} // namespace squid