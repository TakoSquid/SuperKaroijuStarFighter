#pragma once

#include <vector>
#include <functional>
#include <map>

#include "bitmask.hpp"

namespace squid
{
    enum class FacingDirection
    {
        None,
        Left,
        Right,
        Up,
        Down
    };

    struct FrameData
    {
        int id;
        float displayTimeSeconds;
    };

    using AnimationAction = std::function<void(void)>;

    class Animation
    {
    public:
        Animation(FacingDirection direction = FacingDirection::None);

        void AddFrame(int spriteId, float frameTime, bool looped = true);

        const FrameData *GetCurrentFrame() const;

        bool UpdateFrame(float deltaTime);

        void Reset();

        std::vector<int> getFramesSpriteIds();

        void AddFrameAction(unsigned int frame, AnimationAction action);

        void SetLooped(bool looped);
        bool IsLooped();

        void SetDirection(FacingDirection dir);
        FacingDirection GetDirection() const;

    private:
        void IncrementFrame();
        void RunActionForCurrentFrame();

        std::vector<FrameData> frames;
        int currentFrameIndex;
        float currentFrameTime;
        bool releaseFirstFrame;
        std::map<int, std::vector<AnimationAction>> actions;
        Bitmask framesWithActions;
        bool isLooped;
        FacingDirection direction;
    };

} // namespace squid