#include "C_animation.hpp"
#include "Object.hpp"

namespace squid
{
    C_Animation::C_Animation(Object *owner)
        : Component(owner), currentAnimation(AnimationState::None, nullptr)
    {
    }

    int C_Animation::classType()
    {
        return C_ANIMATION;
    }

    void C_Animation::Awake()
    {
        // sprite = owner_->GetComponent<C_Sprite>();
    }

    void C_Animation::Update(float deltaTime)
    {
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

    void C_Animation::AddAnimation(AnimationState state, std::shared_ptr<Animation> animation)
    {
        auto inserted = animations.insert(std::make_pair(state, animation));

        if (currentAnimation.first == AnimationState::None)
            SetAnimationState(state);
    }

    void C_Animation::SetAnimationState(AnimationState state)
    {
        if (currentAnimation.first == state)
        {
            return;
        }

        auto animation = animations.find(state);
        if (animation != animations.end() && sprite)
        {
            currentAnimation.first = animation->first;
            currentAnimation.second = animation->second;

            currentAnimation.second->Reset();

            sprite->Load(currentAnimation.second->GetCurrentFrame()->id);
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

} // namespace squid