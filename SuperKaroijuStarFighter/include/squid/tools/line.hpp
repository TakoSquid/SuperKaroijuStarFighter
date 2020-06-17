#pragma once

#include <m3dia.hpp>

namespace squid
{
    class Line : public m3d::Drawable
    {
    public:
        Line(m3d::Vector2f start, m3d::Vector2f end, m3d::Color col = m3d::Color{255, 255, 255}, float thick = 2.0f);

        void draw(m3d::RenderContext t_context) override;

    private:
        m3d::Vector2f from;
        m3d::Vector2f to;
        m3d::Color color;
        float thickness;
    };
} // namespace squid