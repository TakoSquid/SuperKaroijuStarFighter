#include "C_direction.hpp"
#include "object.hpp"

namespace squid
{
    int C_Direction::classType()
    {
        return C_DIRECTION;
    }

    C_Direction::C_Direction(Object *owner)
        : Component(owner),
          currentDir(FacingDirection::None)
    {
    }

    void C_Direction::Awake()
    {
        velocity = owner_->GetComponent<C_Velocity>();
    }

    FacingDirection C_Direction::Get()
    {

        return FacingDirection::None;

        const m3d::Vector2f &currentVel = velocity->Get();

        if (currentVel.u != 0.0f || currentVel.v != 0.0f)
        {
            float velX = fabs(currentVel.u);
            float velY = fabs(currentVel.v);

            if (velX > velY)
            {
                if (currentVel.u < 0)
                {
                    currentDir = FacingDirection::Left;
                }
                else
                {
                    currentDir = FacingDirection::Right;
                }
            }
            else
            {
                if (currentVel.v < 0)
                {
                    currentDir = FacingDirection::Up;
                }
                else
                {
                    currentDir = FacingDirection::Down;
                }
            }
        }

        return currentDir;
    } // namespace squid

} // namespace squid