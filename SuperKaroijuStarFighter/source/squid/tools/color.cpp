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

m3d::Color rainbow(float ratio)
{
    //we want to normalize ratio so that it fits in to 6 regions
    //where each region is 256 units long
    int normalized = int(fmod(ratio, 1) * 256 * 6);

    //find the distance to the start of the closest region
    int x = normalized % 256;

    int red = 0, grn = 0, blu = 0;
    switch (normalized / 256)
    {
    case 0:
        red = 255;
        grn = x;
        blu = 0;
        break; //red
    case 1:
        red = 255 - x;
        grn = 255;
        blu = 0;
        break; //yellow
    case 2:
        red = 0;
        grn = 255;
        blu = x;
        break; //green
    case 3:
        red = 0;
        grn = 255 - x;
        blu = 255;
        break; //cyan
    case 4:
        red = x;
        grn = 0;
        blu = 255;
        break; //blue
    case 5:
        red = 255;
        grn = 0;
        blu = 255 - x;
        break; //magenta
    }

    return m3d::Color(red, grn, blu);
}
} // namespace squid