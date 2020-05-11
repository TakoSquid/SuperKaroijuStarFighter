#include "object.hpp"

namespace squid
{

Object::Object()
    : queuedForRemoval(false)
{
    transform = AddComponent<C_Transform>();
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
} // namespace squid