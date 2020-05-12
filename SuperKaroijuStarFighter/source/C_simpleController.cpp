#include "C_simpleController.hpp"

#include "squid/engine/object.hpp"
#include "squid/tools/print.hpp"
#include <string>

namespace squid
{
C_SimpleController::C_SimpleController(Object *owner)
    : Component(owner), moveSpeed(100)
{
}

int C_SimpleController::classType()
{
    return C_SIMPLECONTROLLER;
}

void C_SimpleController::SetMovementSpeed(int moveSpeed)
{
    this->moveSpeed = moveSpeed;
}

void C_SimpleController::Update(float deltaTime)
{
    m3d::Vector2f input = m3d::Vector2f{m3d::circlepad::getXPosition() / 155.0f, m3d::circlepad::getYPosition() / 155.0f};

    if (sqrt(input.u * input.u + input.v * input.v) < 0.2f)
    {
        input = {0, 0};
    }

    int xMove = 0;
    xMove = input.u * moveSpeed;

    int yMove = 0;
    yMove = -input.v * moveSpeed;

    float xFrameMove = xMove * deltaTime;
    float yFrameMove = yMove * deltaTime;

    owner_->transform->AddPosition(xFrameMove, yFrameMove);
}

} // namespace squid