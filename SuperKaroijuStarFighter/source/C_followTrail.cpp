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
          m_yOffset{10},
          index{0},
          time{0}
    {
    }

    void C_FollowTrail::Start()
    {
    }

    void C_FollowTrail::Load(unsigned int id)
    {
        if (m_spriteAllocator)
        {
            m3d::Sprite tmp = m_spriteAllocator->getSprite(id);
            tmp.setCenterRel(.5f, .5f);

            m_followSprite.clear();
            m_followSprite.insert(m_followSprite.end(), m_nSprite, tmp);
            m_finished.clear();
            m_finished.insert(m_finished.end(), m_nSprite, false);

            for (size_t i = 0; i < m_followSprite.size(); i++)
            {
                m_followSprite[i].setXPosition(-m_followSprite[i].getSize().u / 2);

                if (i != 0)
                {
                    m_followSprite[i].setOpacity(255.0f * 0.50f);
                    m_followSprite[i].setBlend(1.0f);
                }
            }

            index = m_followSprite.size() - 1;
            time = 0;
        }
    }

    int C_FollowTrail::classType()
    {
        return C_FOLLOWTRAIL;
    }

    void C_FollowTrail::LateUpdate(float deltaTime)
    {
        auto ownerPos = owner_->transform->GetPosition();

        xPos = m_followSprite[index].getXPosition();
        time += deltaTime;
        time = fmod(time, 1);

        if (index < m_followSprite.size())
        {
            if (m_followSprite[index].getXPosition() < ownerPos.u - index * m_distance)
            {
                //xPos += 1000.0f * deltaTime;
                //m_followSprite[index].setXPosition(xPos);

                m_followSprite[index].moveX(2000.0f * deltaTime);
            }
            if (m_followSprite[index].getXPosition() >= ownerPos.u - index * m_distance)
            {
                m_followSprite[index].setXPosition(ownerPos.u - index * m_distance);
                m_finished[index] = true;
                index -= 1;
                xPos = m_followSprite[index].getXPosition();
            }
        }

        for (int i = 0; i < (int)m_followSprite.size(); i++)
        {
            m_followSprite[i].setYPosition(ownerPos.v);

            if (m_finished[i])
            {
                m_followSprite[i].setXPosition(ownerPos.u - i * m_distance);
            }

            m_followSprite[i].moveY(-m_yOffset * sin(m_angle + 3.14f / 16.0f * i));
            if (i != 0)
            {
                m_followSprite[i].setTint(rainbow(time + (float)(i - 1) / ((float)m_followSprite.size() - 2)));
            }
        }

        m_angle += 0.1f;
        m_angle = fmod(m_angle, 6.28f);

        /*for (int i = 0; i < (int)m_followSprite.size(); i++)
        {
            m_followSprite[i].moveY(m_yOffset * sin(m_angle + 3.14f / 16.0f * i));
        }*/
    }

    void C_FollowTrail::Draw(Window &window)
    {
        for (auto it = m_followSprite.rbegin(); it != m_followSprite.rend(); ++it)
        {
            window.Draw(*it);
        }
    }

    void C_FollowTrail::setAllocator(SpriteAllocator *spriteAllocator)
    {
        m_spriteAllocator = spriteAllocator;
    }
} // namespace squid