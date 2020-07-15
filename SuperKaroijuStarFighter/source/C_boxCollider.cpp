#include "C_boxCollider.hpp"
#include "squid/engine/object.hpp"

namespace squid
{
    C_BoxCollider::C_BoxCollider(Object *owner)
        : C_Collider(owner),
          AABB(0, 0, 0, 0),
          offset(m3d::Vector2f{0.0f, 0.0f}),
          rect(0, 0, 0, 0, m3d::Color(0, 0, 0))
    {
    }

    ColliderType C_BoxCollider::getColliderType()
    {
        return ColliderType::Box;
    }

    void C_BoxCollider::SetCollidable(const m3d::BoundingBox &rect)
    {
        AABB = rect;
        SetPosition();
    }

    m3d::BoundingBox &C_BoxCollider::GetCollidable()
    {
        SetPosition();
        return AABB;
    }

    void C_BoxCollider::SetPosition()
    {
        const m3d::Vector2f &pos = owner_->transform->GetPosition();

        AABB.setX(pos.u - (AABB.getWidth() / 2) + offset.u);
        AABB.setY(pos.v - (AABB.getHeight() / 2) + offset.v);
    }

    Manifold C_BoxCollider::Intersects(std::shared_ptr<C_Collider> other)
    {
        Manifold m;
        m.colliding = false;

        if (other->getColliderType() == getColliderType())
        {
            std::shared_ptr<C_BoxCollider> boxCollider = std::static_pointer_cast<C_BoxCollider>(other);

            m3d::BoundingBox &rect1 = GetCollidable();
            m3d::BoundingBox &rect2 = boxCollider->GetCollidable();

            if (rect1.intersects(rect2))
            {
                m.colliding = true;
                m.other = &rect2;
            }
        }

        return m;
    }

    void C_BoxCollider::ResolveOverlap(const Manifold &m)
    {
        auto transform = owner_->transform;

        if (transform->isStatic())
        {
            return;
        }

        m3d::BoundingBox &rect1 = GetCollidable();
        m3d::BoundingBox *rect2 = m.other;

        float resolve = 0;
        float xDiff = (rect1.getX() + (rect1.getWidth() * 0.5f)) - (rect2->getX() + (rect2->getWidth() * 0.5f));
        float yDiff = (rect1.getY() + (rect1.getHeight() * 0.5f)) - (rect2->getY() + (rect2->getHeight() * 0.5f));
        if (fabs(xDiff) > fabs(yDiff))
        {
            if (xDiff > 0)
            {
                resolve = (rect2->getX() + rect2->getWidth()) - rect1.getX();
            }
            else
            {
                resolve = -((rect1.getX() + rect1.getWidth()) - rect2->getX());
            }

            transform->AddPosition(resolve, 0);
        }
        else
        {
            if (yDiff > 0)
            {
                resolve = (rect2->getY() + rect2->getHeight()) - rect1.getY();
            }
            else
            {
                resolve = -((rect1.getY() + rect1.getHeight()) - rect2->getY());
            }

            transform->AddPosition(0, resolve);
        }
    }

    int C_BoxCollider::classType()
    {
        return C_BOXCOLLIDER;
    }

    void C_BoxCollider::Draw(Window &window)
    {
        rect.setXPosition(AABB.getX());
        rect.setYPosition(AABB.getY());
        rect.setWidth(AABB.getWidth());
        rect.setHeight(AABB.getHeight());
        rect.setColor(m3d::Color(255, 0, 0, 50));
        window.Draw(rect);
    }

} // namespace squid