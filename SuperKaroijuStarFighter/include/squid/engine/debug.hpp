#pragma once

#include <array>
#include <iostream>
#include <functional>
#include <m3dia.hpp>

#include "squid/engine/window.hpp"
#include "squid/tools/line.hpp"

namespace squid
{
    class Debug
    {
    public:
        static void Draw(Window &window);

        static void DrawRect(m3d::BoundingBox rect, m3d::Color color = m3d::Color{255, 0, 0});

        static void DrawLine(const m3d::Vector2f from, const m3d::Vector2f to, m3d::Color color = m3d::Color{255, 0, 0}, float thick = 2.5f);

        static void Log(const std::string msg);

        static void LogWarning(const std::string msg);

        static void LogError(const std::string msg);

    private:
        static std::vector<Line> lines;
    };
} // namespace squid