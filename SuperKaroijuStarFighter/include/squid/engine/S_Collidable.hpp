#pragma once

#include <vector>
#include <memory>
#include <set>

#include "squid/engine/object.hpp"
#include "squid/engine/quadtree.hpp"
#include "squid/tools/bitmask.hpp"

namespace squid
{
    class S_Collidable
    {
    public:
        S_Collidable();

        void Add(std::vector<std::shared_ptr<Object>> &objects);
        void ProcessRemovals();
        void Update();

    private:
        void Resolve();
        void ProcessCollisions(std::vector<std::shared_ptr<Object>> &first, std::vector<std::shared_ptr<Object>> &second);

        std::map<CollisionLayer, Bitmask> collisionLayers;
        std::map<CollisionLayer, std::vector<std::shared_ptr<C_BoxCollider>>> collidables;
        Quadtree collisionTree;
    };
} // namespace squid