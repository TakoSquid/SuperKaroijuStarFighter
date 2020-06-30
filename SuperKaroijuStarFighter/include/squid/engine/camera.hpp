#pragma once

#include <m3dia.hpp>
#include "matrix.hpp"

namespace squid
{
    class Camera
    {
    private:
        m3d::Vector2f position;
        m3d::Vector2f size;
        m3d::Vector2f scale;
        float angle;
        bool needToBeUpdated;

        squid::Matrix transformMatrix;
        void updateTransformMatrix();

    public:
        Camera();
        ~Camera();

        Matrix getTransformMatrix();
        bool getNeedToBeUpdated();
        float getAngle();
        m3d::Vector2f getScale();

        m3d::Vector2f worldToCamera(m3d::Vector2f coor);

        void translate(float x, float y);
        void setPosition(float x, float y);
        void rotate(float add);
        void scaling(float x, float y);
        void scaling(float add);
    };
} // namespace squid