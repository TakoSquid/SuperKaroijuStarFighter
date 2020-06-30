#include "object.hpp"

namespace squid
{

    Object::Object()
        : queuedForRemoval(false),
          sortOrder(0)
    {
        transform = AddComponent<C_Transform>();
        instanceID = AddComponent<C_InstanceID>();
    }

    void Object::Awake()
    {
        for (int i = components_.size() - 1; i >= 0; i--)
        {
            components_[i]->Awake();
        }
    }

    void Object::Start()
    {
        for (int i = components_.size() - 1; i >= 0; i--)
        {
            components_[i]->Start();
        }
    }

    void Object::Update(float timeDelta)
    {
        for (int i = components_.size() - 1; i >= 0; i--)
        {
            components_[i]->Update(timeDelta);
        }
    }

    void Object::LateUpdate(float timeDelta)
    {
        for (int i = components_.size() - 1; i >= 0; i--)
        {
            components_[i]->LateUpdate(timeDelta);
        }
    }

    void Object::Draw(Window &window)
    {
        transform->AddX(20.0f);
        for (int i = components_.size() - 1; i >= 0; i--)
        {
            components_[i]->Draw(window);
        }
        transform->AddX(-20.0f);
    }

    void Object::QueueForRemoval()
    {
        queuedForRemoval = true;
    }

    bool Object::IsQueuedForRemoval()
    {
        return queuedForRemoval;
    }

    void Object::SetSortOrder(int order)
    {
        sortOrder = order;
    }

    int Object::GetSortOrder() const
    {
        return sortOrder;
    }
} // namespace squid