#include "C_transform.hpp"

#include <iostream>

namespace squid
{
    C_Transform::C_Transform(Object *owner)
        : Component(owner), position_{0.f, 0.f}, angle_(0), isStaticTransform(false)
    {
    }

    int C_Transform::classType()
    {
        return C_TRANSFORM;
    }

    void C_Transform::SetPosition(float x, float y)
    {
        position_.u = x;
        position_.v = y;
    }

    void C_Transform::SetPosition(const m3d::Vector2f &pos)
    {
        position_ = pos;
    }

    void C_Transform::AddPosition(float x, float y)
    {
        position_.u += x;
        position_.v += y;
    }

    void C_Transform::AddPosition(m3d::Vector2f pos)
    {
        AddPosition(pos.u, pos.v);
    }

    void C_Transform::SetX(float x)
    {
        position_.u = x;
    }

    void C_Transform::SetY(float y)
    {
        position_.v = y;
    }

    void C_Transform::AddX(float x)
    {
        position_.u += x;
    }

    void C_Transform::AddY(float y)
    {
        position_.v = y;
    }

    const m3d::Vector2f &C_Transform::GetPosition() const
    {
        return position_;
    }

    void C_Transform::Draw(Window &window)
    {
        //std::cout << "Position : " << position_.u << '|' << position_.v << std::endl;
    }

    void C_Transform::SetStatic(bool isStatic)
    {
        isStaticTransform = isStatic;
    }

    bool C_Transform::isStatic() const
    {
        return isStaticTransform;
    }

    void C_Transform::SetAngle(float a)
    {
        angle_ = a;
    }

    void C_Transform::Rotate(float a)
    {
        SetAngle(angle_ + a);
    }
    float C_Transform::GetAngle() const
    {
        return angle_;
    }
} // namespace squid