#include "C_scrollingBackground.hpp"

namespace squid
{
C_ScrollingBackground::C_ScrollingBackground(Object *owner)
    : Component(owner),
      m_mainSpr{"romfs:/gfx/images.t3x", 3},
      m_followSpr{m_mainSpr},
      m_speed{100}
{
}

int C_ScrollingBackground::classType()
{
    return C_SCROLLINGBACKGROUND;
}

void C_ScrollingBackground::SetSpriteId(int id)
{
    m_mainSpr = m3d::Sprite{"romfs:/gfx/images.t3x", id};
    m_followSpr = m_mainSpr;
    m_mainSpr.setCenterRel(0.5f, 0.5f);
    m_followSpr.setCenterRel(0.5f, 0.5f);
    m_mainSpr.setPosition(200, 120);
    m_followSpr.setPosition(200 + m_mainSpr.getSize().u, 120);
}
void C_ScrollingBackground::SetSpeed(float speed)
{
    m_speed = speed;
}

void C_ScrollingBackground::Start()
{
    SetSpriteId(3);
}

void C_ScrollingBackground::Update(float deltaTime)
{
    m_mainSpr.moveX(-m_speed * deltaTime);
    m_followSpr.setPosition(m_mainSpr.getXPosition() + m_mainSpr.getSize().u, m_mainSpr.getYPosition());

    if (m_followSpr.getXPosition() <= 200)
    {
        m_mainSpr.setPosition(200, 120);
    }
}

void C_ScrollingBackground::Draw(Window &window)
{
    window.Draw(m_mainSpr);
    window.Draw(m_followSpr);
}
} // namespace squid