#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "squid/engine/object.hpp"
#include "squid/engine/S_Collidable.hpp"
#include "squid/engine/camera.hpp"

namespace squid
{
    class ObjectCollection
    {
    public:
        void Add(std::shared_ptr<Object> object);

        void Update(float deltaTime);
        void LateUpdate(float deltaTime);

        void Draw(Window &window);

        void ProcessNewObjects();
        void ProcessRemovals();
        void QueueEveryObjects();

        unsigned int getNumberObjects();

        squid::Camera *getCamera();

    private:
        //void Sort();
        std::vector<std::shared_ptr<Object>> objects;
        std::vector<std::shared_ptr<Object>> newObjects;
        S_Collidable collidables;
        squid::Camera cam;

        // static bool LayerSort(std::shared_ptr<Object> a, std::shared_ptr<Object> b);
    };
} // namespace squid