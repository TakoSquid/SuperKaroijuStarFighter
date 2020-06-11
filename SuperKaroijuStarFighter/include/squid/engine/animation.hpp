#pragma once

#include <vector>

namespace squid
{

    struct FrameData
    {
        int id;
        float displayTimeSeconds;
    };

    class Animation
    {
    public:
        Animation();

        void AddFrame(int spriteId, float frameTime);

        const FrameData *GetCurrentFrame() const;

        bool UpdateFrame(float deltaTime);

        void Reset();

        std::vector<int> getFramesSpriteIds();

    private:
        void IncrementFrame();

        std::vector<FrameData> frames;
        int currentFrameIndex;
        float currentFrameTime;
    };

} // namespace squid