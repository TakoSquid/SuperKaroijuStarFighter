#pragma once

#include "squid/engine/component.hpp"

namespace squid
{
class C_Sprite : public Component
{
public:
    C_Sprite(Object *owner);
    int classType() override;

    void Load(int id);
    void LateUpdate(float deltaTime) override;
    void Draw(Window &window) override;

private:
    m3d::Sprite spr_;
};
} // namespace squid