#include "C_sprite.hpp"

#include "squid/engine/object.hpp"

#include "squid/tools/print.hpp"
#include <string>
#include <iostream>

namespace squid
{
    C_Sprite::C_Sprite(Object *owner)
        : Component(owner),
          currentScale{1.0f, 1.0f},
          centerRel{0.5f, 0.5f},
          needToBeUpdated{true}
    {
    }

    int C_Sprite::classType()
    {
        return C_SPRITE;
    }

    void C_Sprite::Load(int id)
    {
        if (owner_->context->spriteAllocator && id >= 0)
            spr_ = owner_->context->spriteAllocator->getSprite(id);
    }

    void C_Sprite::Start()
    {
        spr_.setPosition(owner_->transform->GetPosition());
        spr_.setRotation(owner_->transform->GetAngle());
    }

    void C_Sprite::LateUpdate(float deltaTime)
    {

        spr_.setPosition(owner_->transform->GetPosition());
        spr_.setRotation(owner_->transform->GetAngle());

        if (needToBeUpdated)
        {
            spr_.setScale(currentScale);
            spr_.setCenterRel(centerRel.u, centerRel.v);

            needToBeUpdated = false;
        }
    }

    void C_Sprite::Draw(Window &window)
    {
        if (auto c = owner_->cam)
        {
            spr_.setPosition(c->worldToCamera(spr_.getPosition()));
            spr_.setRotation(spr_.getRotation() + c->getAngle() / M_PI * 180.0f);

            spr_.setXScale(spr_.getXScale());
            spr_.setYScale(spr_.getYScale());

            auto tmp = c->getScale();

            spr_.setXScale(currentScale.u * tmp.u);
            spr_.setYScale(currentScale.v * tmp.v);
        }

        window.Draw(spr_, m3d::RenderContext::Mode::Flat, owner_->GetSortOrder());
    }

    void C_Sprite::setOpacity(float opacity)
    {
        spr_.setOpacity(255 * opacity);

        needToBeUpdated = true;
    }

    void C_Sprite::setTint(m3d::Color tint)
    {
        spr_.setTint(tint);
        spr_.setBlend(tint.getAlpha() / 255.0f);

        needToBeUpdated = true;
    }

    // void C_Sprite::setAllocator(SpriteAllocator *spriteAllocator)
    // {
    //     // m_SpriteAllocator = spriteAllocator;
    // }

    // SpriteAllocator *C_Sprite::getAllocator()
    // {
    //     // return m_SpriteAllocator;
    // }

    m3d::Vector2f C_Sprite::getSize()
    {
        return spr_.getSize();
    }

    void C_Sprite::setCenter(m3d::Vector2f center)
    {
        centerRel = center;

        needToBeUpdated = true;
    }

    void C_Sprite::flipX(bool flipX)
    {
        if (flipX)
            currentScale.u = -1.0f;

        needToBeUpdated = true;
    }
    void C_Sprite::flipY(bool flipY)
    {
        if (flipY)
            currentScale.v *= -1.0f;

        needToBeUpdated = true;
    }

    void C_Sprite::setScale(m3d::Vector2f scale)
    {
        currentScale = scale;

        needToBeUpdated = true;
    }

} // namespace squid