#pragma once

#include "squid/engine/window.hpp"

#define C_SPRITE 1
#define C_TRANSFORM 2
#define C_SIMPLECONTROLLER 3
#define C_SCROLLINGBACKGROUND 4
#define C_FOLLOWTRAIL 5
#define C_OFFSETPAD 6
#define C_GOTOWARDS 7
#define C_ANIMATION 8
#define C_BLINKING 9
#define C_INSTANCEID 10
#define C_BOXCOLLIDER 11

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
        Object *owner_;
    };
} // namespace squid