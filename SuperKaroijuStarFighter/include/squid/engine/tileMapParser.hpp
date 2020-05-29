#pragma once

#include <memory>
#include <string>
#include <vector>
#include <m3dia.hpp>

#include "squid/engine/tile.hpp"
#include "squid/engine/spriteAllocator.hpp"
#include "squid/engine/object.hpp"

namespace squid
{
    using Layer = std::vector<std::shared_ptr<Tile>>;
    using MapTiles = std::map<std::string, std::shared_ptr<Layer>>;
    using TileSet = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;

    struct TileSheetData
    {
        SpriteAllocator &spriteAllocator;
        m3d::Vector2f tileSize;
    };

    class TileMapParser
    {
    public:
        TileMapParser(SpriteAllocator &spriteAllocator);

        std::vector<std::shared_ptr<Object>> Parse(const std::string &file, m3d::Vector2f offset);

    private:
        std::shared_ptr<TileSheetData> BuildTileSheetData();

        SpriteAllocator &m_spriteAllocator;
    };
} // namespace squid