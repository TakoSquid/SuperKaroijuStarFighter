#pragma once

#include <vector>
#include <m3dia.hpp>
#include "squid/engine/component.hpp"

namespace squid
{
class C_FollowTrail : public Component
{
public:
    C_FollowTrail(Object *owner);
    int classType() override;

    void Start() override;
    void LateUpdate(float deltaTime) override;
    void Draw(Window &window) override;

private:
    std::vector<m3d::Sprite> m_followSprite;
    float m_angle;
    unsigned int m_nSprite;
    float m_distance;
    float m_yOffset;
};
} // namespace squid