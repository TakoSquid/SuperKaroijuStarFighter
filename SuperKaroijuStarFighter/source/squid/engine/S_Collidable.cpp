#include "S_Collidable.hpp"

namespace squid
{
    int S_Collidable::nbAddCalled = 0;

    S_Collidable::S_Collidable()
    {
        Bitmask defaultCollisions;
        defaultCollisions.SetBit((int)CollisionLayer::Default);
        collisionLayers.insert(std::make_pair(CollisionLayer::Default, defaultCollisions));

        collisionLayers.insert(std::make_pair(CollisionLayer::Tile, Bitmask(0)));

        Bitmask playerCollisions;
        playerCollisions.SetBit((int)CollisionLayer::Default);
        playerCollisions.SetBit((int)CollisionLayer::Tile);
        collisionLayers.insert(std::make_pair(CollisionLayer::Player, playerCollisions));
    }

    void S_Collidable::Add(std::vector<std::shared_ptr<Object>> &objects)
    {

        for (auto o : objects)
        {
            auto collider = o->GetComponent<C_BoxCollider>();

            if (collider)
            {

                CollisionLayer layer = collider->GetLayer();

                auto itr = collidables.find(layer);

                if (itr != collidables.end())
                {
                    collidables[layer].push_back(collider);
                }
                else
                {
                    std::vector<std::shared_ptr<C_BoxCollider>> objs;
                    objs.push_back(collider);

                    collidables.insert(std::make_pair(layer, objs));
                }
            }
        }
    }

    void S_Collidable::ProcessRemovals()
    {
        for (auto &layer : collidables)
        {
            auto itr = layer.second.begin();
            while (itr != layer.second.end())
            {
                if ((*itr)->owner_->IsQueuedForRemoval())
                {
                    itr = layer.second.erase(itr);
                }
                else
                {
                    ++itr;
                }
            }
        }
    }

    void S_Collidable::Update()
    {

        collisionTree.DrawDebug();

        collisionTree.Clear();

        for (auto maps = collidables.begin(); maps != collidables.end(); ++maps)
        {
            for (auto collidable : maps->second)
            {
                collisionTree.Insert(collidable);
            }
        }

        Resolve();
    }

    void S_Collidable::Resolve()
    {

        nbAddCalled = 0;

        for (auto maps = collidables.begin(); maps != collidables.end(); ++maps)
        {

            if (collisionLayers[maps->first].GetMask() == 0)
            {
                continue;
            }

            for (auto collidable : maps->second)
            {
                if (collidable->owner_->transform->isStatic())
                {
                    continue;
                }

                std::vector<std::shared_ptr<C_BoxCollider>> collisions = collisionTree.Search(collidable->GetCollidable());

                for (auto collision : collisions)
                {

                    if (collidable->owner_->instanceID->Get() == collision->owner_->instanceID->Get())
                    {
                        continue;
                    }

                    collisionLayers[collidable->GetLayer()].GetBit(((int)collision->GetLayer()));

                    // TODO
                    bool layersCollide = true;
                    // TMP

                    if (layersCollide)
                    {
                        Manifold m = collidable->Intersects(collision);

                        nbAddCalled += 1;

                        if (m.colliding)
                        {

                            if (collision->owner_->transform->isStatic())
                            {
                                collidable->ResolveOverlap(m);
                            }
                            else
                            {

                                collidable->ResolveOverlap(m);
                            }
                        }
                    }
                }
            }
        }
    }
} // namespace squid