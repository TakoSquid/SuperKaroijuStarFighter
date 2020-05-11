#pragma once

#include <vector>
#include <memory>

#include "squid/engine/window.hpp"
#include "squid/engine/component.hpp"
#include "C_transform.hpp"

namespace squid
{
class Object
{
public:
    Object();

    void Awake(); //Make sure requiered compo is present
    void Start(); //Init variables

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window &window);

    template <typename T>
    std::shared_ptr<T> AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value,
                      "T must derive from Component");

        std::shared_ptr<T> newComponent = std::make_shared<T>(this);

        for (auto &exisitingComponent : components_)
        {
            if (newComponent->classType() == exisitingComponent->classType())
            {
                return std::static_pointer_cast<T>(exisitingComponent);
            }
        }

        components_.push_back(newComponent);

        return newComponent;
    };

    template <typename T>
    std::shared_ptr<T> GetComponent()
    {
        static_assert(std::is_base_of<Component, T>::value,
                      "T must derive from Component");

        std::shared_ptr<T> newComponent = std::make_shared<T>(this);

        for (auto &exisitingComponent : components_)
        {
            if (newComponent->classType() == exisitingComponent->classType())
            {
                return std::static_pointer_cast<T>(exisitingComponent);
            }
        }

        return nullptr;
    };

    std::shared_ptr<C_Transform> transform;

private:
    std::vector<std::shared_ptr<Component>> components_;
};
} // namespace squid