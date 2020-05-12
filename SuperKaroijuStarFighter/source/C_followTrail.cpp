#include "C_followTrail.hpp"

#include "squid/engine/object.hpp"
#include "squid/tools/color.hpp"

#include <iostream>

namespace squid
{
C_FollowTrail::C_FollowTrail(Object *owner)
    : Component{owner},
      m_angle{0.0f},
      m_nSprite{10},
      m_distance{10},
      m_yOffset{50}
{
}

void C_FollowTrail::Start()
{
    m3d::Sprite tmp{"romfs:/gfx/images.t3x", 1};
    tmp.setCenterRel(.5f, .5f);

    m_followSprite.insert(m_followSprite.end(), m_nSprite, tmp);

    for (size_t i = 0; i < m_followSprite.size(); i++)
    {
        m_followSprite[i].setXPosition(m_followSprite[i].getSize().u);

        if (i != 0)
        {
            m_followSprite[i].setOpacity(255.0f * 0.50f);
            m_followSprite[i].setBlend(1.0f);
        }
    }
}

int C_FollowTrail::classType()
{
    return C_FOLLOWTRAIL;
}

void C_FollowTrail::LateUpdate(float deltaTime)
{
    auto ownerPos = owner_->transform->GetPosition();

    static unsigned int index = 0;

    static float time = 0;
    time += deltaTime;
    time = fmod(time, 1);

    for (int i = 0; i < (int)m_followSprite.size(); i++)
    {
        //m_followSprite[i].setPosition(ownerPos.u - i * m_distance, ownerPos.v);
        m_followSprite[i].moveY(-m_yOffset * sin(m_angle + 3.14f / 16.0f * i));
        if (i != 0)
        {
            m_followSprite[i].setTint(rainbow(time + (float)(i - 1) / ((float)m_followSprite.size() - 2)));
        }
    }

    m_angle += 0.1f;
    m_angle = fmod(m_angle, 6.28f);

    for (int i = 0; i < (int)m_followSprite.size(); i++)
    {
        m_followSprite[i].moveY(m_yOffset * sin(m_angle + 3.14f / 16.0f * i));
    }
}

void C_FollowTrail::Draw(Window &window)
{
    for (auto it = m_followSprite.rbegin(); it != m_followSprite.rend(); ++it)
    {
        window.Draw(*it);
    }
}
} // namespace squid