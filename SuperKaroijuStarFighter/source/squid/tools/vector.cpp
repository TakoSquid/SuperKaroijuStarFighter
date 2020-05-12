#include "vector.hpp"

namespace squid
{

float distance(m3d::Vector2f a, m3d::Vector2f b)
{
    return sqrt((a.u - b.u) * (a.u - b.u) + (a.v - b.v) * (a.v - b.v));
}

bool is_between(m3d::Vector2f a, m3d::Vector2f c, m3d::Vector2f b)
{
    return distance(a, c) + distance(c, b) == distance(a, b);
}

} // namespace squid
