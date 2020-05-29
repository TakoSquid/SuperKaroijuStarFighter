#include "C_blinking.hpp"

namespace squid
{
    C_Blinking::C_Blinking(Object *owner)
        : Component(owner),
          m_timer{0},
          m_timeGoal{1.0f},
          m_toggle{true}
    {
    }

    int C_Blinking::classType()
    {
        return C_BLINKING;
    }

    void C_Blinking::setTimeGoal(float time)
    {
        m_timeGoal = time;
    }

    void C_Blinking::Awake()
    {
        m_sprite = owner_->GetComponent<C_Sprite>();
    }

    void C_Blinking::Update(float deltaTime)
    {
        m_timer += deltaTime;

        if (m_timer >= m_timeGoal)
        {
            if (m_sprite)
            {
                m_toggle = !m_toggle;
                m_sprite->setOpacity((float)m_toggle);
            }
            m_timer = 0;
        }
    }

} // namespace squid