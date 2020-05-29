#include "C_offsetPad.hpp"
#include "squid/engine/object.hpp"
namespace squid
{
    C_OffsetPad::C_OffsetPad(Object *owner)
        : Component(owner),
          offset{0.0f, 0.0f},
          m_magnitude(0)
    {
    }

    int C_OffsetPad::classType()
    {
        return C_OFFSETPAD;
    }

    void C_OffsetPad::Start()
    {
        offset = m3d::Vector2f{0, 0};
    }

    void C_OffsetPad::setMagnitude(float magnitude)
    {
        m_magnitude = magnitude;
    }

    void C_OffsetPad::LateUpdate(float deltaTime)
    {
        owner_->transform->AddPosition(-1 * offset);

        m3d::Vector2f input = m3d::Vector2f{m3d::circlepad::getXPosition() / 155.0f, -m3d::circlepad::getYPosition() / 155.0f};
        offset = input * m_magnitude;

        owner_->transform->AddPosition(offset);
    }
} // namespace squid