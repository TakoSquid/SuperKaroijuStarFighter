#include "animation.hpp"

namespace squid
{

    Animation::Animation()
        : frames(0),
          currentFrameIndex(0),
          currentFrameTime(0)
    {
    }

    void Animation::AddFrame(int spriteId, float frameTime)
    {
        FrameData data;
        data.id = spriteId;
        data.displayTimeSeconds = frameTime;

        frames.push_back(data);
    }

    const FrameData *Animation::GetCurrentFrame() const
    {
        if (frames.size() > 0)
            return &frames[currentFrameIndex];

        return nullptr;
    }

    bool Animation::UpdateFrame(float deltaTime)
    {
        if (frames.size() > 0)
        {
            currentFrameTime += deltaTime;

            if (currentFrameTime >= frames[currentFrameIndex].displayTimeSeconds)
            {
                currentFrameTime = 0.0f;
                IncrementFrame();
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
        currentFrameTime = 0;
    }
} // namespace squid