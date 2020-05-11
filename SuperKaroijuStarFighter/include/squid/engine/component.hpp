#pragma once

#include "squid/engine/window.hpp"

#define C_SPRITE 1
#define C_TRANSFORM 2
#define C_SIMPLECONTROLLER 3

namespace squid
{

class Object;

class Component
{
public:
    Component(Object *owner);

    virtual void Awake();
    virtual void Start();

    virtual void Update(float deltaTime);
    virtual void LateUpdate(float deltaTime);
    virtual void Draw(Window &window);

    virtual int classType() = 0;

protected:
    Object *owner_;
};
} // namespace squid