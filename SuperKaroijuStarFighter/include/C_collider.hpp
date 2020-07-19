#pragma once

#include <memory>
#include <m3dia.hpp>

#include "squid/engine/component.hpp"

namespace squid
{

    enum class CollisionLayer
    {
        Default = 1,
        Player = 2,
        Tile = 3,
        Projectile = 4
    };

    struct Manifold
    {
        bool colliding = false;
        m3d::BoundingBox *other;
    };

    enum ColliderType
    {
        Box
    };

    class C_Collider : public Component
    {
    public:
        C_Collider(Object *owner);
        ~C_Collider();

        virtual Manifold Intersects(std::shared_ptr<C_Collider> other) = 0;
        virtual void ResolveOverlap(const Manifold &m) = 0;
        virtual ColliderType getColliderType() = 0;

        CollisionLayer GetLayer() const;
        void SetLayer(CollisionLayer layerd);

        bool IsTrigger() const;
        void SetTrigger(bool isTrigger);

    private:
        CollisionLayer layer;
        bool isTrigger;
    };

} // namespace squid