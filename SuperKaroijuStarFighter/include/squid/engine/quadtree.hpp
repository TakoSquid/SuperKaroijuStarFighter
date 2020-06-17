#pragma once

#include <memory>
#include <vector>

#include "C_boxCollider.hpp"
#include "Object.hpp"
// #include "debug.hpp"

namespace squid
{
    class Quadtree
    {
    public:
        Quadtree();
        Quadtree(int maxObjects, int maxLevels, int level, m3d::BoundingBox, Quadtree *parent);

        void Insert(std::shared_ptr<C_BoxCollider> object);
        void Remove(std::shared_ptr<C_BoxCollider> object);
        void Clear();

        std::vector<std::shared_ptr<C_BoxCollider>> Search(m3d::BoundingBox &area);
        m3d::BoundingBox &GetBounds();

        void DrawDebug();

    private:
        void Search(m3d::BoundingBox &area, std::vector<std::shared_ptr<C_BoxCollider>> &overlappingObjects);
        int GetChildIndexForObject(m3d::BoundingBox &objectBounds);
        void Split();

        static const int thisTree = -1;
        static const int childNE = 0;
        static const int childNW = 1;
        static const int childSW = 2;
        static const int childSE = 3;

        int maxObjects;
        int maxLevels;

        std::shared_ptr<Quadtree> children[4];
        std::vector<std::shared_ptr<C_BoxCollider>> objects;
        int level;
        m3d::BoundingBox &bounds;
        Quadtree *parent;
    };
} // namespace squid