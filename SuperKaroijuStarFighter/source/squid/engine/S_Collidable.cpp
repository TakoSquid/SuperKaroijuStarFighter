#include "S_Collidable.hpp"

namespace squid
{

    S_Collidable::S_Collidable()
    {
        Bitmask defaultCollisions;
        defaultCollisions.SetBit((int)CollisionLayer::Default);
        collisionsLayers.insert(std::make_pair(CollisionLayer::Default, defaultCollisions));

        collisionsLayers.insert(std::make_pair(CollisionLayer::Tile, Bitmask(0)));

        Bitmask playerCollisions;
        playerCollisions.SetBit((int)CollisionLayer::Default);
        playerCollisions.SetBit((int)CollisionLayer::Tile);
        collisionsLayers.insert(std::make_pair(CollisionLayer::Player, playerCollisions));

        Bitmask projectileCollisions;
        projectileCollisions.SetBit((int)CollisionLayer::Tile);
        collisionsLayers.insert(std::make_pair(CollisionLayer::Projectile, projectileCollisions));
    }

    void S_Collidable::Add(std::vector<std::shared_ptr<Object>> &objects)
    {

        for (auto o : objects)
        {
            auto collider = o->GetComponent<C_BoxCollider>();

            if (collider)
            {

                o->context->collisionTree = getCollisionTree();

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
        if (collidables.size() > 0)
            std::cout << "Collidables : " << collidables.size() << std::endl;

        ProcessCollidingObjects();

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

        for (auto maps = collidables.begin(); maps != collidables.end(); ++maps)
        {

            if (collisionsLayers[maps->first].GetMask() == 0)
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

                    bool layersCollide = collisionsLayers[collidable->GetLayer()].GetBit(((int)collision->GetLayer()));

                    if (layersCollide)
                    {
                        Manifold m = collidable->Intersects(collision);

                        if (m.colliding)
                        {
                            auto collisionPair = objectsColliding.emplace(std::make_pair(collidable, collision));

                            if (collisionPair.second)
                            {
                                collidable->owner_->OnCollisionEnter(collision);
                                collision->owner_->OnCollisionEnter(collidable);
                            }

                            if (!collision->IsTrigger() && !collidable->IsTrigger())
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
    }

    void S_Collidable::ProcessCollidingObjects()
    {

        auto itr = objectsColliding.begin();
        while (itr != objectsColliding.end())
        {

            auto pair = *itr;

            std::shared_ptr<C_BoxCollider> first = pair.first;
            std::shared_ptr<C_BoxCollider> second = pair.second;

            if (first->owner_->IsQueuedForRemoval() || second->owner_->IsQueuedForRemoval())
            {

                first->owner_->OnCollisionExit(second);
                second->owner_->OnCollisionExit(first);

                itr = objectsColliding.erase(itr);
            }
            else
            {
                Manifold m = first->Intersects(second);

                if (!m.colliding)
                {
                    first->owner_->OnCollisionExit(second);
                    second->owner_->OnCollisionExit(first);

                    itr = objectsColliding.erase(itr);
                }
                else
                {
                    first->owner_->OnCollisionStay(second);
                    second->owner_->OnCollisionStay(first);

                    ++itr;
                }
            }
        }
    }

    Quadtree *S_Collidable::getCollisionTree()
    {
        return &collisionTree;
    }

} // namespace squid