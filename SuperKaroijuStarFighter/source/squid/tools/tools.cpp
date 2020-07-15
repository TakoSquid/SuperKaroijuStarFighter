#include "tools.hpp"

namespace squid
{
    m3d::Vector2f lerp(m3d::Vector2f a, m3d::Vector2f b, float t, bool clamped)
    {
        if (clamped)
            t = std::clamp(t, 0.0f, 1.0f);

        return m3d::Vector2f{std::lerp(a.u, b.u, t), std::lerp(a.v, b.v, t)};
    }

    float lerp(float a, float b, float t, bool clamped)
    {
        if (clamped)
        {
            t = std::clamp(t, 0.0f, 1.0f);
        }

        return std::lerp(a, b, t);
    }

} // namespace squid