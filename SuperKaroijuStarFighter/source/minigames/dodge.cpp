#include "dodge.hpp"

#include "squid/engine/object.hpp"

#include "C_boxCollider.hpp"
#include "C_sprite.hpp"
#include "C_velocity.hpp"
#include "C_simpleController.hpp"

namespace squid
{
    Dodge::Dodge(SharedContext *context, unsigned int difficulty)
        : MiniGame(context, difficulty, 3, true)
    {
    }

    std::vector<std::shared_ptr<Object>> Dodge::buildObjects()
    {
        std::vector<std::shared_ptr<Object>> objs;

        auto machin = std::make_shared<Object>(context);
        machin->AddComponent<C_Velocity>();
        machin->AddComponent<C_SimpleController>();
        auto box = machin->AddComponent<C_BoxCollider>();
        box->SetCollidable(m3d::BoundingBox{0, 0, 30, 30});

        objs.emplace_back(machin);

        return objs;
    }
} // namespace squid