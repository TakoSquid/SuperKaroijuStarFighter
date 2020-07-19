#pragma once

#include <vector>
#include <memory>

#include "sharedContext.hpp"
#include "squid/engine/object.hpp"

namespace squid
{
    class MiniGame
    {
    public:
        MiniGame(SharedContext *context);
        MiniGame(SharedContext *context, unsigned int dif, float dur, bool isWon);

        std::vector<std::shared_ptr<Object>> getObjects();

    protected:
        SharedContext *context;

    private:
        std::vector<std::shared_ptr<Object>> objects;

        unsigned int difficulty;
        float duration;
        bool isWon;

        virtual std::vector<std::shared_ptr<Object>> buildObjects();
    };
} // namespace squid