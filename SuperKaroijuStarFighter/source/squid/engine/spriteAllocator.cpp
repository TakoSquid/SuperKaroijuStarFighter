#include "spriteAllocator.hpp"

namespace squid
{

    SpriteAllocator::SpriteAllocator(std::string spriteSheetPath)
        : m_spriteSheetPath(spriteSheetPath),
          done(false)
    {
    }

    m3d::Sprite SpriteAllocator::getSprite(unsigned int id)
    {
        auto it = m_sprites.find(id);

        if (it != m_sprites.end())
        {
            return it->second;
        }
        else
        {
            m_sprites[id] = m3d::Sprite(m_spriteSheetPath, id);
            m_sprites[id].setCenterRel(0.5f, 0.5f);
            return m_sprites[id];
        }

        return m_sprites[id];
    }

    unsigned int SpriteAllocator::nLoadedSprites()
    {
        return m_sprites.size();
    }
} // namespace squid