#pragma once

#include <memory>

#include "squid/engine/spriteAllocator.hpp"

namespace squid
{
    struct TileInfo
    {
        TileInfo()
            : tileID(-1)
        {
        }

        TileInfo(unsigned int tileID)
            : tileID(tileID)
        {
        }
        int tileID;
    };

    struct Tile
    {
        std::shared_ptr<TileInfo> properties;
        int x;
        int y;
    };

} // namespace squid