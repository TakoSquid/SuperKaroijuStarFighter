#pragma once

#include "spriteAllocator.hpp"
#include "window.hpp"

namespace squid
{
    class ObjectCollection;

    struct SharedContext
    {
        ObjectCollection *objects;
        SpriteAllocator *spriteAllocator;
        Window *window;
    };
} // namespace squid