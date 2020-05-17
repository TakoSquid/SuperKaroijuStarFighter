#pragma once

#include <iostream>
#include <map>
#include <m3dia.hpp>

namespace squid
{
    class SpriteAllocator
    {
    public:
        m3d::Sprite getSprite(unsigned int id);
        unsigned int nLoadedSprites();

    private:
        std::map<int, m3d::Sprite> m_sprites;
    };
} // namespace squid