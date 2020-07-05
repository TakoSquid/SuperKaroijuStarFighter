#include "C_animation.hpp"
#include "Object.hpp"

namespace squid
{
    C_Animation::C_Animation(Object *owner)
        : Component(owner),
          currentAnimation(AnimationState::None, nullptr),
          currentDirection(FacingDirection::None)
    {
    }

    int C_Animation::classType()
    {
        return C_ANIMATION;
    }

    void C_Animation::Awake()
    {
        sprite = owner_->GetComponent<C_Sprite>();
        direction = owner_->GetComponent<C_Direction>();
    }

    void C_Animation::Update(float deltaTime)
    {
        SetAnimationDirection(direction->Get());

        if (currentAnimation.first != AnimationState::None && sprite)
        {
            bool newFrame = currentAnimation.second->UpdateFrame(deltaTime);

            if (newFrame)
            {
                const FrameData *data = currentAnimation.second->GetCurrentFrame();
                sprite->Load(data->id);
            }
        }
    }

    void C_Animation::AddAnimation(AnimationState state, AnimationList &animationList)
    {
        animations.insert(std::make_pair(state, animationList));

        if (currentAnimation.first == AnimationState::None)
            SetAnimationState(state);

        for (auto const &anim : animationList)
        {
            for (auto const &id : anim.second->getFramesSpriteIds())
            {
                owner_->context->spriteAllocator->getSprite(id);
            }
        }
    }

    void C_Animation::SetAnimationState(AnimationState state)
    {
        if (currentAnimation.first == state)
        {
            return;
        }

        auto animationList = animations.find(state);
        if (animationList != animations.end() && sprite)
        {

            auto animation = animationList->second.find(currentDirection);

            if (animation != animationList->second.end())
            {
                currentAnimation.first = animationList->first;
                currentAnimation.second = animation->second;
                currentAnimation.second->Reset();
            }
        }
    }

    const AnimationState &C_Animation::GetAnimationState() const
    {
        return currentAnimation.first;
    }

    void C_Animation::setSprite(std::shared_ptr<squid::C_Sprite> spr)
    {
        sprite = spr;
    }

    void C_Animation::SetAnimationDirection(FacingDirection dir)
    {
        if (dir != currentDirection)
        {
            currentDirection = dir;

            auto animationList = animations.find(currentAnimation.first);
            if (animationList != animations.end())
            {
                auto animation = animationList->second.find(currentDirection);
                if (animation != animationList->second.end())
                {
                    currentAnimation.second = animation->second;
                    currentAnimation.second->Reset();
                }
            }
        }
    }

    void C_Animation::AddAnimationAction(AnimationState state, FacingDirection dir, int frame, AnimationAction action)
    {
        auto animationList = animations.find(state);

        if (animationList != animations.end())
        {
            auto animation = animationList->second.find(dir);
            {
                if (animation != animationList->second.end())
                {
                    animation->second->AddFrameAction(frame, action);
                }
            }
        }
    }

} // namespace squid