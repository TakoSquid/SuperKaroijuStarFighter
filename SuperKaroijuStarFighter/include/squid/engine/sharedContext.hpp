#pragma once

#include "spriteAllocator.hpp"
#include "window.hpp"
#include "Quadtree.hpp"

namespace squid
{
    class ObjectCollection;
    class Quadtree;

    struct SharedContext
    {
        ObjectCollection *objects;
        SpriteAllocator *spriteAllocator;
        Window *window;
        Quadtree *collisionTree;
    };
} // namespace squid