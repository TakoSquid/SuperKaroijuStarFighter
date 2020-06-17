#include "quadtree.hpp"

namespace squid
{
    Quadtree::Quadtree() : Quadtree(5, 5, 0, m3d::BoundingBox(0.0f, 0.0f, 400, 240), nullptr) {}

    Quadtree::Quadtree(int maxObjects, int maxLevels, int level, m3d::BoundingBox bounds, Quadtree *parent)
        : maxObjects(maxObjects),
          maxLevels(maxLevels),
          level(level),
          bounds(bounds),
          parent(parent) {}

    void Quadtree::Insert(std::shared_ptr<C_BoxCollider> object)
    {
        if (children[0])
        {
            int indexToPlaceObject = GetChildIndexForObject(object->GetCollidable());

            if (indexToPlaceObject != thisTree)
            {
                children[indexToPlaceObject]->Insert(object);
                return;
            }
        }

        objects.emplace_back(object);

        if ((int)(objects.size()) > maxObjects && level < maxLevels && children[0] == nullptr)
        {
            Split();

            auto objIterator = objects.begin();
            while (objIterator != objects.end())
            {
                auto obj = *objIterator;
                int indexToPlaceObject = GetChildIndexForObject(obj->GetCollidable());

                if (indexToPlaceObject != thisTree)
                {
                    children[indexToPlaceObject]->Insert(obj);
                    objIterator = objects.erase(objIterator);
                }
                else
                {
                    ++objIterator;
                }
            }
        }
    }

    void Quadtree::Remove(std::shared_ptr<C_BoxCollider> object)
    {
        int index = GetChildIndexForObject(object->GetCollidable());

        if (index == thisTree || children[index] == nullptr)
        {
            for (size_t i = 0; i < objects.size(); i++)
            {
                if (objects.at(i)->owner_->instanceID->Get() == object->owner_->instanceID->Get())
                {
                    objects.erase(objects.begin() + i);
                    break;
                }
            }
        }
        else
        {
            return children[index]->Remove(object);
        }
    }

    void Quadtree::Clear()
    {
        objects.clear();

        for (size_t i = 0; i < 4; i++)
        {
            if (children[i])
            {
                children[i]->Clear();
                children[i] = nullptr;
            }
        }
    }

    std::vector<std::shared_ptr<C_BoxCollider>> Quadtree::Search(m3d::BoundingBox &area)
    {
        std::vector<std::shared_ptr<C_BoxCollider>> possibleOverlaps;
        Search(area, possibleOverlaps);

        std::vector<std::shared_ptr<C_BoxCollider>> returnList;

        for (auto collider : possibleOverlaps)
        {
            if (area.intersects(collider->GetCollidable()))
            {
                returnList.emplace_back(collider);
            }
        }

        return returnList;
    }

    void Quadtree::Search(m3d::BoundingBox &area, std::vector<std::shared_ptr<C_BoxCollider>> &overlappingObjects)
    {
        overlappingObjects.insert(overlappingObjects.end(), objects.begin(), objects.end());

        if (children[0])
        {
            int index = GetChildIndexForObject(area);

            if (index == thisTree)
            {
                for (size_t i = 0; i < 4; i++)
                {
                    if (children[i]->GetBounds().intersects(area))
                    {
                        children[i]->Search(area, overlappingObjects);
                    }
                }
            }
            else
            {
                children[index]->Search(area, overlappingObjects);
            }
        }
    }

    int Quadtree::GetChildIndexForObject(m3d::BoundingBox &objectBounds)
    {
        int index = -1;

        double verticalDividingLine = bounds.getX() + bounds.getWidth() * 0.5f;
        double horizontalDividingLine = bounds.getY() + bounds.getHeight() * 0.5f;

        bool north = objectBounds.getY() < horizontalDividingLine && (objectBounds.getHeight() + objectBounds.getY() < horizontalDividingLine);
        bool south = objectBounds.getY() > horizontalDividingLine;
        bool west = objectBounds.getX() < verticalDividingLine && (objectBounds.getX() + objectBounds.getWidth() < verticalDividingLine);
        bool east = objectBounds.getX() > verticalDividingLine;

        if (east)
        {
            if (north)
            {
                index = childNE;
            }
            else if (south)
            {
                index = childSE;
            }
        }
        else if (west)
        {
            if (north)
            {
                index = childNW;
            }
            else if (south)
            {
                index = childSW;
            }
        }

        return index;
    }

    m3d::BoundingBox &Quadtree::GetBounds()
    {
        return bounds;
    }

    void Quadtree::Split()
    {
        const int childWidth = bounds.getWidth() / 2;
        const int childHeight = bounds.getHeight() / 2;

        children[childNE] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
                                                       m3d::BoundingBox(bounds.getX() + childWidth, bounds.getY(), childWidth, childHeight),
                                                       this);
        children[childNW] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
                                                       m3d::BoundingBox(bounds.getX(), bounds.getY(), childWidth, childHeight),
                                                       this);
        children[childSW] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
                                                       m3d::BoundingBox(bounds.getX(), bounds.getY() + childHeight, childWidth, childHeight),
                                                       this);
        children[childSE] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
                                                       m3d::BoundingBox(bounds.getX() + childWidth, bounds.getY() + childHeight, childWidth, childHeight),
                                                       this);
    }

    void Quadtree::DrawDebug()
    {
        if (children[0] != nullptr)
        {
            for (int i = 0; i < 4; i++)
            {
                children[i]->DrawDebug();
            }
        }

        // Debug::DrawRect(bounds);
    }

} // namespace squid