#pragma once

#include <m3dia.hpp>

namespace squid
{
m3d::Color gradiant(m3d::Color c1, m3d::Color c2, float t);

m3d::Color rainbow(float ratio);

} // namespace squid