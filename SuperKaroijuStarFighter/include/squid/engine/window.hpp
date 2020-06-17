#pragma once

#include <m3dia.hpp>

namespace squid
{
    class Window
    {
    public:
        Window(bool enable3d);

        void Update();

        void BeginDraw();
        void Draw(m3d::Drawable &drawable);
        void EndDraw();

        bool IsOpen() const;

    private:
        m3d::Screen scr;
    };

} // namespace squid