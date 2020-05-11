#include "C_sprite.hpp"

#include "squid/engine/object.hpp"

namespace squid
{
C_Sprite::C_Sprite(Object *owner)
    : Component(owner)
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
}

void C_Sprite::LateUpdate(float deltaTime)
{
    spr_.setPosition(owner_->transform->GetPosition());
}

void C_Sprite::Draw(Window &window)
{
    window.Draw(spr_);
}

} // namespace squid