#pragma once

#include <memory>

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
#define C_PROJECTILEATTACK 12
#define C_VELOCITY 13
#define C_MOVEMENTANIMATION 14
#define C_DIRECTION 15
#define C_REMOVEOBJECTONCOLLISIONENTER 16

namespace squid
{

    class Object;
    class C_BoxCollider;

    class Component
    {
    public:
        Component(Object *owner);

        virtual void Awake();
        virtual void Start();

        virtual void Update(float deltaTime);
        virtual void LateUpdate(float deltaTime);
        virtual void Draw(Window &window);

        virtual void OnCollisionEnter(std::shared_ptr<C_BoxCollider> other);
        virtual void OnCollisionStay(std::shared_ptr<C_BoxCollider> other);
        virtual void OnCollisionExit(std::shared_ptr<C_BoxCollider> other);

        virtual int classType() = 0;
        Object *owner_;
    };
} // namespace squid