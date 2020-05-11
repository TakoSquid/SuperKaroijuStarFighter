#pragma once

#include <memory>
#include <vector>

#include "squid/engine/object.hpp"

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

private:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Object>> newObjects;
};
} // namespace squid