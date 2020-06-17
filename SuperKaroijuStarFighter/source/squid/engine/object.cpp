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
        for (int i = components_.size() - 1; i >= 0; i--)
        {
            components_[i]->Draw(window);
        }
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

    void Object::SetDrawLayer(DrawLayer drawLayer)
    {
        layer = drawLayer;
    }

    DrawLayer Object::GetDrawLayer() const
    {
        return layer;
    }
} // namespace squid