#include "line.hpp"

namespace squid
{
    Line::Line(m3d::Vector2f start, m3d::Vector2f end, m3d::Color col, float thick)
        : from(start),
          to(end),
          color{col},
          thickness(thick)
    {
    }

    void Line::draw(m3d::RenderContext t_context)
    {
        C2D_DrawLine(from.u, from.v, color.getRgba8(), to.u, to.v, color.getRgba8(), thickness, 0);
    }

} // namespace squid