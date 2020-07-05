#include "tileMapParser.hpp"

namespace squid
{
    TileMapParser::TileMapParser(SharedContext &context)
        : m_sharedContext(context)
    {
    }

    std::vector<std::shared_ptr<Object>> TileMapParser::Parse(const std::string &file, m3d::Vector2f offset)
    {
        tinyxml2::XMLDocument xmlDoc;
        xmlDoc.LoadFile(file.c_str()); //YOLO
        tinyxml2::XMLElement *rootNode = xmlDoc.FirstChildElement("map");

        std::shared_ptr<MapTiles> tiles = BuildMapTiles(rootNode);

        int tileSizeX;
        rootNode->QueryIntAttribute("tilewidth", &tileSizeX);
        int tileSizeY;
        rootNode->QueryIntAttribute("tileheight", &tileSizeY);
        int mapSizeX;
        rootNode->QueryIntAttribute("width", &mapSizeX);
        int mapSizeY;
        rootNode->QueryIntAttribute("height", &mapSizeY);

        std::vector<std::shared_ptr<Object>> tileObjects;

        int lay = 0;

        for (const auto &layer : *tiles)
        {
            for (const auto &tile : layer.second->tiles)
            {
                std::shared_ptr<TileInfo> tileInfo = tile->properties;
                std::shared_ptr<Object> tileObject = std::make_shared<Object>(&m_sharedContext);

                const float tileScale = 1.0f;

                auto sprite = tileObject->AddComponent<C_Sprite>();
                sprite->Load(tile->properties->tileID - 1);
                sprite->setScale(m3d::Vector2f{tileScale, tileScale});
                sprite->setOpacity(layer.second->opacity);

                float x = tile->x * tileSizeX * tileScale + offset.u;
                float y = tile->y * tileSizeY * tileScale + offset.v;

                tileObject->transform->SetPosition(x, y);
                tileObject->SetSortOrder(lay);

                if (layer.first == "1 - Collisions")
                {
                    auto collider = tileObject->AddComponent<C_BoxCollider>();
                    float left = x - (tileSizeX * tileScale) * 0.5f;
                    float top = y - (tileSizeY * tileScale) * 0.5f;
                    float width = tileSizeX * tileScale;
                    float height = tileSizeY * tileScale;

                    collider->SetCollidable(m3d::BoundingBox(left, top, width, height));
                    collider->SetLayer(CollisionLayer::Tile);
                }

                tileObjects.emplace_back(tileObject);
            }

            lay += 1;
        }

        return tileObjects;
    }

    std::shared_ptr<MapTiles> TileMapParser::BuildMapTiles(tinyxml2::XMLElement *rootNode)
    {
        std::shared_ptr<TileSheetData> tileSheetData = BuildTileSheetData(rootNode);
        std::shared_ptr<MapTiles> map = std::make_shared<MapTiles>();

        for (tinyxml2::XMLElement *e = rootNode->FirstChildElement("layer"); e != nullptr; e = e->NextSiblingElement("layer"))
        {
            std::pair<std::string, std::shared_ptr<Layer>> mapLayer = BuildLayer(e, tileSheetData);

            map->emplace_back(mapLayer);
        }

        return map;
    }

    std::shared_ptr<TileSheetData>
    TileMapParser::BuildTileSheetData(tinyxml2::XMLElement *rootNode)
    {
        TileSheetData tileSheetData;

        tileSheetData.nbSprites = -1;

        rootNode->QueryFloatAttribute("tilewidth", &tileSheetData.tileSize.u);
        rootNode->QueryFloatAttribute("tileheight", &tileSheetData.tileSize.v);

        return std::make_shared<TileSheetData>(tileSheetData);
    }

    std::pair<std::string, std::shared_ptr<Layer>> TileMapParser::BuildLayer(tinyxml2::XMLElement *layerNode, std::shared_ptr<TileSheetData> tileSheetData)
    {
        TileSet tileSet;
        std::shared_ptr<Layer> layer = std::make_shared<Layer>();

        int width;
        layerNode->QueryIntAttribute("width", &width);
        int height;
        layerNode->QueryIntAttribute("width", &height);

        float opacity = 1.0f;

        if (layerNode->QueryFloatAttribute("opacity", &opacity) == tinyxml2::XML_NO_ATTRIBUTE)
        {
            opacity = 1.0f;
        }

        layer->opacity = opacity;

        tinyxml2::XMLElement *dataNode = layerNode->FirstChildElement("data");

        std::string rawData = dataNode->GetText();
        rawData.erase(std::remove(rawData.begin(), rawData.end(), '\r'), rawData.end());
        rawData.erase(std::remove(rawData.begin(), rawData.end(), '\n'), rawData.end());

        std::stringstream ss(rawData);
        std::vector<int> tileIds;

        for (int i; ss >> i;)
        {
            tileIds.push_back(i);
            if (ss.peek() == ',')
                ss.ignore();
        }

        for (size_t i = 0; i < tileIds.size(); i++)

        {
            if (tileIds[i] != 0)
            {
                auto itr = tileSet.find(tileIds[i]);
                if (itr == tileSet.end())
                {
                    std::shared_ptr<TileInfo> tileInfo = std::make_shared<TileInfo>(tileIds[i]);
                    itr = tileSet.insert(std::make_pair(tileIds[i], tileInfo)).first;
                }

                std::shared_ptr<Tile> tile = std::make_shared<Tile>();

                tile->properties = itr->second;
                tile->x = i % width;
                tile->y = i / width;

                layer->tiles.emplace_back(tile);
            }
        }

        const std::string layerName = layerNode->Attribute("name");
        return std::make_pair(layerName, layer);
    }

} // namespace squid