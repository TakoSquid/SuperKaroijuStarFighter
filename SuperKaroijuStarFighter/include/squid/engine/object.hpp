#pragma once

#include <vector>
#include <memory>

#include "squid/engine/window.hpp"
#include "squid/engine/component.hpp"
#include "C_transform.hpp"
#include "C_instanceId.hpp"
#include "camera.hpp"
#include "squid/engine/sharedContext.hpp"

namespace squid
{

    class Object
    {
    public:
        Object(SharedContext *c);
        SharedContext *context;

        void Awake();
        void Start();

        void Update(float deltaTime);
        void LateUpdate(float deltaTime);

        void Draw(Window &window);

        bool IsQueuedForRemoval();
        void QueueForRemoval();

        template <typename T>
        std::shared_ptr<T> AddComponent()
        {

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

        void SetSortOrder(int order);
        int GetSortOrder() const;

        void OnCollisionEnter(std::shared_ptr<C_BoxCollider> other);
        void OnCollisionStay(std::shared_ptr<C_BoxCollider> other);
        void OnCollisionExit(std::shared_ptr<C_BoxCollider> other);

        std::shared_ptr<C_Transform> transform;
        std::shared_ptr<C_InstanceID> instanceID;
        Camera *cam;

    private:
        std::vector<std::shared_ptr<Component>> components_;
        bool queuedForRemoval;

        int sortOrder;
    };
} // namespace squid