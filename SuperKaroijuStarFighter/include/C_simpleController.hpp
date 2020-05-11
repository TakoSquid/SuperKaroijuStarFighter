#pragma once

#include "squid/engine/component.hpp"

namespace squid
{
class C_SimpleController : public Component
{
public:
    C_SimpleController(Object *owner);
    int classType() override;

    void SetMovementSpeed(int moveSpeed);

    void Update(float deltaTime) override;

private:
    int moveSpeed;
};
} // namespace squid