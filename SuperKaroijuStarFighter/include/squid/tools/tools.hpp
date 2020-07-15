#pragma once

#include <m3dia.hpp>
#include <algorithm>
#include <cmath>

namespace squid
{
    m3d::Vector2f lerp(m3d::Vector2f a, m3d::Vector2f b, float t, bool clamped = true);

    float lerp(float a, float b, float t, bool clamped = true);
} // namespace squid