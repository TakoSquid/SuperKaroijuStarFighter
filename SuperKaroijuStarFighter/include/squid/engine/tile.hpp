#pragma once

#include <memory>

#include "squid/engine/spriteAllocator.hpp"

namespace squid
{
    struct TileInfo
    {
        /*TileInfo() : tileID(-1)
        {
        }*/

        TileInfo(SpriteAllocator &spraloc, unsigned int tileID)
            : spriteAllocator(spraloc),
              tileID(tileID)
        {
        }

        int tileID;
        SpriteAllocator &spriteAllocator;
    };

    struct Tile
    {
        std::shared_ptr<TileInfo> properties;
        int x;
        int y;
    };

} // namespace squid