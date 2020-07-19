#pragma once

#include "miniGame.hpp"

namespace squid
{
    class Dodge : public MiniGame
    {
    public:
        Dodge(SharedContext *context, unsigned int difficulty);

    private:
        std::vector<std::shared_ptr<Object>> buildObjects() override;
    };
} // namespace squid