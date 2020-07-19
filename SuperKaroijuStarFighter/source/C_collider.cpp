#include "C_collider.hpp"

namespace squid
{
    C_Collider::C_Collider(Object *owner)
        : Component(owner),
          layer(CollisionLayer::Default),
          isTrigger(false)
    {
    }

    C_Collider::~C_Collider() {}

    CollisionLayer C_Collider::GetLayer() const
    {
        return layer;
    }

    void C_Collider::SetLayer(CollisionLayer layer)
    {
        this->layer = layer;
    }

    bool C_Collider::IsTrigger() const
    {
        return isTrigger;
    }

    void C_Collider::SetTrigger(bool isTrigger)
    {
        this->isTrigger = isTrigger;
    }
} // namespace squid