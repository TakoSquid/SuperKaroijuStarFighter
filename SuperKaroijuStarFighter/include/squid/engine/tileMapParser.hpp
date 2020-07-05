#pragma once

#include <memory>
#include <string>
#include <vector>
#include <m3dia.hpp>
#include <unordered_map>
#include <sstream>
#include <algorithm>

#include "squid/engine/tile.hpp"
#include "squid/engine/spriteAllocator.hpp"
#include "squid/engine/object.hpp"
#include "squid/engine/sharedContext.hpp"

#include "C_sprite.hpp"
#include "C_boxCollider.hpp"

#include "tinyxml2.h"

namespace squid
{

    struct Layer
    {
        std::vector<std::shared_ptr<Tile>> tiles;
        float opacity;
    };

    using MapTiles = std::vector<std::pair<std::string, std::shared_ptr<Layer>>>;
    using TileSet = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;

    struct TileSheetData
    {
        int nbSprites;
        m3d::Vector2f tileSize;
    };

    class TileMapParser
    {
    public:
        TileMapParser(SharedContext &context);

        std::vector<std::shared_ptr<Object>> Parse(const std::string &file, m3d::Vector2f offset);

    private:
        std::shared_ptr<TileSheetData> BuildTileSheetData(tinyxml2::XMLElement *rootNode);
        std::shared_ptr<MapTiles> BuildMapTiles(tinyxml2::XMLElement *rootNode);
        std::pair<std::string, std::shared_ptr<Layer>> BuildLayer(tinyxml2::XMLElement *layerNode, std::shared_ptr<TileSheetData> tileSheetData);
        SharedContext &m_sharedContext;
    };
} // namespace squid