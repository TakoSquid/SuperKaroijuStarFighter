#include "squid/engine/objectCollection.hpp"

namespace squid
{

    void ObjectCollection::Update(float deltaTime)
    {
        for (auto &o : objects)
            o->Update(deltaTime);

        collidables.Update();
    }

    void ObjectCollection::LateUpdate(float deltaTime)
    {
        for (auto &o : objects)
            o->LateUpdate(deltaTime);
    }

    void ObjectCollection::Draw(Window &window)
    {
        for (auto &o : objects)
            o->Draw(window);

        std::cout << "Nb Collidables : " << S_Collidable::nbAddCalled << std::endl;
    }

    void ObjectCollection::Add(std::shared_ptr<Object> object)
    {
        newObjects.push_back(object);
    }

    void ObjectCollection::ProcessNewObjects()
    {
        if (newObjects.size() > 0)
        {
            for (const auto &o : newObjects)
            {
                o->Awake();
            }

            for (const auto &o : newObjects)
            {
                o->Start();
            }

            objects.insert(objects.end(), newObjects.begin(), newObjects.end());

            collidables.Add(newObjects);

            newObjects.clear();

            Sort();
        }
    }

    void ObjectCollection::ProcessRemovals()
    {
        bool removed = false;
        auto objIterator = objects.begin();

        while (objIterator != objects.end())
        {
            auto obj = *objIterator;

            if (obj->IsQueuedForRemoval())
            {
                objIterator = objects.erase(objIterator);
                removed = true;
            }
            else
            {
                ++objIterator;
            }
        }

        if (removed)
        {
            collidables.ProcessRemovals();
        }
    }

    unsigned int ObjectCollection::getNumberObjects()
    {
        return objects.size();
    }

    void ObjectCollection::Sort()
    {
        std::sort(
            objects.begin(), objects.end(),
            [](std::shared_ptr<Object> a, std::shared_ptr<Object> b) -> bool {
                return a->GetSortOrder() < b->GetSortOrder();
            });
    }
} // namespace squid