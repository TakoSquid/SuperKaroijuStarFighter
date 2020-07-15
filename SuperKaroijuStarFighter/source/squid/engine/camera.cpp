#include "camera.hpp"

namespace squid
{
    Camera::Camera()
        : position{-200.0f, -120.0f}, size{400.0f, 240.0f}, scale{1.0f, 1.0f}, angle{0}, needToBeUpdated{true}, transformMatrix{createIdentity(3)}
    {
    }

    Camera::~Camera()
    {
    }

    void Camera::updateTransformMatrix()
    {
        // transformMatrix = squid::createScaleMatrix(scale) * squid::createTranslationMatrix(position);
        transformMatrix = squid::multiply(createScaleMatrix(scale), squid::createTranslationMatrix(position));
        // transformMatrix = createRotationMatrix(angle) * transformMatrix;
        transformMatrix = squid::multiply(createRotationMatrix(angle), transformMatrix);
        // transformMatrix = createTranslationMatrix(size / 2) * transformMatrix;
        transformMatrix = squid::multiply(createTranslationMatrix(size / 2), transformMatrix);

        needToBeUpdated = false;
    }

    Matrix Camera::getTransformMatrix()
    {
        if (needToBeUpdated)
            updateTransformMatrix();

        return transformMatrix;
    }

    bool Camera::getNeedToBeUpdated()
    {
        return needToBeUpdated;
    }

    float Camera::getAngle()
    {
        return angle;
    }

    m3d::Vector2f Camera::getScale()
    {
        return scale;
    }

    m3d::Vector2f Camera::worldToCamera(m3d::Vector2f coor)
    {
        return multiply(getTransformMatrix(), coor);
    }

    // Sprite Camera::displaySprite(Sprite *spr)
    // {
    //     squid::Sprite newSprite = *spr;
    //     squid::Vector2 spritePos(newSprite.params.pos.x, newSprite.params.pos.y);

    //     squid::scaleSprite(&newSprite, scale);
    //     squid::rotationSprite(&newSprite, angle);
    //     squid::positionSprite(&newSprite, worldToCamera(spritePos));

    //     squid::drawSprite(&newSprite);

    //     return newSprite;
    // }

    void Camera::setPosition(float x, float y)
    {
        needToBeUpdated = true;
        position.u = x;
        position.v = y;
    }

    void Camera::setPosition(m3d::Vector2f pos)
    {
        needToBeUpdated = true;
        position.u = pos.u;
        position.v = pos.v;
    }

    void Camera::translate(float x, float y)
    {
        needToBeUpdated = true;

        position.u += x;
        position.v += y;
    }

    void Camera::rotate(float add)
    {
        needToBeUpdated = true;

        angle += add;
    }

    void Camera::scaling(float x, float y)
    {
        needToBeUpdated = true;
        scale.u += x;
        scale.v += y;
    }

    void Camera::scaling(float add)
    {
        scaling(add, add);
    }

    void Camera::setScale(float x, float y)
    {
        needToBeUpdated = true;
        scale.u = x;
        scale.v = y;
    }
    void Camera::setScale(float val)
    {
        setScale(val, val);
    }

} // namespace squid