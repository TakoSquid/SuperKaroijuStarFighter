#pragma once

#include <iostream>
#include <map>
#include <m3dia.hpp>
#include <string>

namespace squid
{
    class SpriteAllocator
    {
    public:
        SpriteAllocator(std::string spriteSheetPath);

        m3d::Sprite getSprite(unsigned int id);
        unsigned int nLoadedSprites();

    private:
        std::string m_spriteSheetPath;
        std::map<int, m3d::Sprite> m_sprites;
    };
} // namespace squid