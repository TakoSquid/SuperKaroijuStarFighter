#pragma once

#include <memory>

#include "squid/engine/component.hpp"
#include "squid/engine/animation.hpp"
#include "C_sprite.hpp"
#include "C_direction.hpp"

namespace squid
{

    enum class AnimationState
    {
        None,
        Idle,
        Walk,
        SlowFly,
        Casting
    };

    using AnimationList = std::map<FacingDirection, std::shared_ptr<Animation>>;

    class C_Animation : public Component
    {
    public:
        C_Animation(Object *owner);

        int classType() override;

        void Awake() override;
        void Update(float deltaTime) override;

        void AddAnimation(AnimationState state, AnimationList &animationList);

        void SetAnimationState(AnimationState state);
        const AnimationState &GetAnimationState() const;

        void setSprite(std::shared_ptr<squid::C_Sprite> spr);
        void SetAnimationDirection(FacingDirection dir);

        void AddAnimationAction(AnimationState, FacingDirection dir, int frame, AnimationAction action);

    private:
        std::shared_ptr<C_Sprite> sprite;
        std::unordered_map<AnimationState, AnimationList> animations;
        std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
        std::shared_ptr<C_Direction> direction;
        FacingDirection currentDirection;
    };

} // namespace squid