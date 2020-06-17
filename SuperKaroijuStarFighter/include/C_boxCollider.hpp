#pragma once

#include "squid/engine/component.hpp"
#include "C_collider.hpp"

namespace squid
{
    class C_BoxCollider : public C_Collider
    {
    public:
        C_BoxCollider(Object *owner); // Done

        Manifold Intersects(std::shared_ptr<C_Collider> other) override; //Done
        void ResolveOverlap(const Manifold &m) override;
        ColliderType getColliderType() override; // Done
        int classType() override;

        void SetCollidable(const m3d::BoundingBox &rect); // Done
        m3d::BoundingBox &GetCollidable();                // Done

        void Draw(Window &window) override;

    private:
        void SetPosition();

        m3d::BoundingBox AABB;
        m3d::Vector2f offset;
        m3d::Rectangle rect;
    };
} // namespace squid