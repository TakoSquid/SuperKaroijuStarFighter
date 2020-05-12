#pragma once

#include <m3dia.hpp>

namespace squid
{

float distance(m3d::Vector2f a, m3d::Vector2f b);

bool is_between(m3d::Vector2f a, m3d::Vector2f c, m3d::Vector2f b);
} // namespace squid