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

    void Start() override;
    void LateUpdate(float deltaTime) override;
    void Draw(Window &window) override;

    void setOpacity(float opacity);
    void setTint(m3d::Color tint);

    m3d::Vector2f getSize();

private:
    m3d::Sprite spr_;
};
} // namespace squid