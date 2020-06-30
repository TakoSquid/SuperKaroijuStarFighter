#include "window.hpp"

namespace squid
{
    Window::Window(bool enable3d)
        : scr(enable3d)
    {
        scr.setClearColor(m3d::Color(255, 0, 255));
    }

    void Window::Update()
    {
    }

    void Window::BeginDraw()
    {
    }

    void Window::Draw(m3d::Drawable &drawable, m3d::RenderContext::Mode mode, int layer)
    {
        scr.drawTop(drawable, mode, layer);
    }

    void Window::EndDraw()
    {
        scr.render();
    }

    bool Window::IsOpen() const
    {
        return true;
    }
} // namespace squid