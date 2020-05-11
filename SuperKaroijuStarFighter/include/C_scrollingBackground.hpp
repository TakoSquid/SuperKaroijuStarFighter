#pragma once

#include <m3dia.hpp>
#include "squid/engine/component.hpp"
#include "squid/engine/object.hpp"

namespace squid
{
class C_ScrollingBackground : public Component
{
public:
    C_ScrollingBackground(Object *owner);

    int classType();
    void SetSpriteId(int id);
    void SetSpeed(float speed);

    void Start() override;
    void Update(float deltaTime) override;
    void Draw(Window &window) override;

private:
    m3d::Sprite m_mainSpr;
    m3d::Sprite m_followSpr;
    float m_speed;
};

} // namespace squid