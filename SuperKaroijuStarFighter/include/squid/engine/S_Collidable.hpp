#pragma once

#include <vector>
#include <memory>
#include <set>
#include <unordered_set>

#include "squid/engine/object.hpp"
#include "squid/engine/quadtree.hpp"
#include "squid/tools/bitmask.hpp"
#include "squid/engine/EnumClassHash.hpp"
#include "squid/engine/ComponentPairHash.hpp"

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
        void ProcessCollidingObjects();

        Quadtree collisionTree;

        std::unordered_map<CollisionLayer, Bitmask, EnumClassHash> collisionsLayers;
        std::unordered_map<CollisionLayer, std::vector<std::shared_ptr<C_BoxCollider>>, EnumClassHash> collidables;
        std::unordered_set<std::pair<std::shared_ptr<C_BoxCollider>, std::shared_ptr<C_BoxCollider>>, ComponentPairHash> objectsColliding;
    };
} // namespace squid