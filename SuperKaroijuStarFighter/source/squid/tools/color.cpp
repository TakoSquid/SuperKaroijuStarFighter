#include "color.hpp"

namespace squid
{
m3d::Color gradiant(m3d::Color c1, m3d::Color c2, float t)
{
    if (t <= 0.0f)
        return c1;

    if (t >= 1.0f)
        return c2;

    return m3d::Color{uint8_t(c1.getRed() + t * (c2.getRed() - c1.getRed())), (uint8_t)(c1.getGreen() + t * (c2.getGreen() - c1.getGreen())), (uint8_t)(c1.getBlue() + c2.getBlue() - c1.getBlue()), (uint8_t)(c1.getAlpha() + t * (c2.getAlpha() - c1.getAlpha()))};
}
} // namespace squid