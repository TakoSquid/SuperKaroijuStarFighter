#pragma once

#include <memory>

#include "squid/engine/component.hpp"
#include "squid/engine/animation.hpp"
#include "C_sprite.hpp"

namespace squid
{

    enum class AnimationState
    {
        None,
        Idle,
        Walk,
        SlowFly
    };

    class C_Animation : public Component
    {
    public:
        C_Animation(Object *owner);

        int classType() override;

        void Awake() override;
        void Update(float deltaTime) override;

        void AddAnimation(AnimationState state, std::shared_ptr<Animation> animation);

        void SetAnimationState(AnimationState state);

        const AnimationState &GetAnimationState() const;

    private:
        std::shared_ptr<C_Sprite> sprite;
        std::map<AnimationState, std::shared_ptr<Animation>> animations;

        std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
    };

} // namespace squid