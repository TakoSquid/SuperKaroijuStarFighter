#include "animation.hpp"

namespace squid
{

    Animation::Animation(FacingDirection direction)
        : frames(0),
          currentFrameIndex(0),
          currentFrameTime(0),
          releaseFirstFrame(true),
          isLooped(true),
          direction(direction)
    {
    }

    void Animation::AddFrame(int spriteId, float frameTime, bool looped)
    {
        FrameData data;
        data.id = spriteId;
        data.displayTimeSeconds = frameTime;

        frames.push_back(data);

        isLooped = looped;
    }

    const FrameData *Animation::GetCurrentFrame() const
    {
        if (frames.size() > 0)
            return &frames[currentFrameIndex];

        return nullptr;
    }

    bool Animation::UpdateFrame(float deltaTime)
    {
        if (releaseFirstFrame)
        {
            RunActionForCurrentFrame();
            releaseFirstFrame = false;
            return true;
        }

        if (frames.size() > 1 && (isLooped || currentFrameIndex < frames.size() - 1))
        {
            currentFrameTime += deltaTime;

            if (currentFrameTime >= frames[currentFrameIndex].displayTimeSeconds)
            {
                currentFrameTime = 0.0f;
                IncrementFrame();
                RunActionForCurrentFrame();
                return true;
            }
        }

        return false;
    }

    void Animation::IncrementFrame()
    {
        currentFrameIndex = (currentFrameIndex + 1) % frames.size();
    }

    void Animation::Reset()
    {
        currentFrameIndex = 0;
        currentFrameTime = 0.0f;
        releaseFirstFrame = true;
    }

    std::vector<int> Animation::getFramesSpriteIds()
    {
        std::vector<int> framesIds;

        for (const auto &frame : frames)
        {
            framesIds.emplace_back(frame.id);
        }

        return framesIds;
    }

    void Animation::AddFrameAction(unsigned int frame, AnimationAction action)
    {
        if (frame < frames.size())
        {
            auto actionKey = actions.find(frame);

            if (actionKey == actions.end())
            {
                framesWithActions.SetBit(frame);
                actions.insert(std::make_pair(frame, std::vector<AnimationAction>{action}));
            }
            else
            {
                actionKey->second.emplace_back(action);
            }
        }
    }

    void Animation::RunActionForCurrentFrame()
    {
        if (actions.size() > 0)
        {

            if (framesWithActions.GetBit(currentFrameIndex))
            {
                auto actionsToRun = actions[currentFrameIndex];

                for (auto f : actionsToRun)
                {
                    f();
                }
            }
        }
    }

    void Animation::SetLooped(bool looped)
    {
        isLooped = looped;
    }

    bool Animation::IsLooped()
    {
        return isLooped;
    }

    void Animation::SetDirection(FacingDirection dir)
    {
        if (direction != dir)
        {
            direction = dir;
        }
    }

    FacingDirection Animation::GetDirection() const
    {
        return direction;
    }
} // namespace squid