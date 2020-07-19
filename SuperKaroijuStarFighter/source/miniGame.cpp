#include "miniGame.hpp"

namespace squid
{
    MiniGame::MiniGame(SharedContext *context)
        : context{context},
          difficulty{0},
          duration{5},
          isWon{false}
    {
    }

    MiniGame::MiniGame(SharedContext *context, unsigned int dif, float dur, bool isWon)
        : context{context},
          difficulty{dif},
          duration{dur},
          isWon{isWon}
    {
    }

    std::vector<std::shared_ptr<Object>> MiniGame::getObjects()
    {
        if (objects.size() == 0)
            objects = buildObjects();

        return objects;
    }

    std::vector<std::shared_ptr<Object>> MiniGame::buildObjects()
    {
        std::vector<std::shared_ptr<Object>> empty;

        return empty;
    }
} // namespace squid