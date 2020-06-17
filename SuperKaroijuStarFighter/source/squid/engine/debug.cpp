#include "squid/engine/debug.hpp"

namespace squid
{
    std::vector<Line> Debug::lines = {};

    void Debug::Draw(Window &window)
    {

        for (auto &l : lines)
        {
            window.Draw(l);
        }

        lines.clear();
    }

    void Debug::DrawRect(m3d::BoundingBox rect, m3d::Color color)
    {

        DrawLine(m3d::Vector2f{rect.getX(), rect.getY()}, m3d::Vector2f{rect.getX() + rect.getWidth(), rect.getY()});
        DrawLine(m3d::Vector2f{rect.getX(), rect.getY() + rect.getHeight()}, m3d::Vector2f{rect.getX() + rect.getWidth(), rect.getY() + rect.getHeight()});
        DrawLine(m3d::Vector2f{rect.getX(), rect.getY()}, m3d::Vector2f{rect.getX(), rect.getY() + rect.getHeight()});
        DrawLine(m3d::Vector2f{rect.getX() + rect.getWidth(), rect.getY()}, m3d::Vector2f{rect.getX() + rect.getWidth(), rect.getY() + rect.getHeight()});

        DrawLine(m3d::Vector2f{0, 0}, m3d::Vector2f{400, 240});
    }

    void Debug::DrawLine(const m3d::Vector2f from, const m3d::Vector2f to, m3d::Color color, float thick)
    {
        Line l{from, to, color, thick};

        lines.push_back(l);
    }

    void Debug::Log(const std::string msg)
    {
        std::cout << msg << std::endl;
    }

    void Debug::LogWarning(const std::string msg)
    {
        std::cout << "WARNING: " << msg << std::endl;
    }

    void Debug::LogError(const std::string msg)
    {
        std::cout << "ERROR: " << msg << std::endl;
    }
} // namespace squid