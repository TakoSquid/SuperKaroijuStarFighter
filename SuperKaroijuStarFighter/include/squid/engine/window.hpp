#pragma once

#include <m3dia.hpp>
#include "camera.hpp"

namespace squid
{
    class Window
    {
    public:
        Window(bool enable3d);

        void Update();

        void BeginDraw();
        void Draw(m3d::Drawable &drawable, m3d::RenderContext::Mode mode = m3d::RenderContext::Mode::Flat, int layer = 0);
        void EndDraw();

        bool IsOpen() const;

    private:
        m3d::Screen scr;
    };

} // namespace squid