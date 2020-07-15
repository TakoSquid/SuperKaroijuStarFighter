#pragma once

#include "component.hpp"
#include "C_animation.hpp"
#include "C_removeObjectOnCollisionEnter.hpp"
#include "objectCollection.hpp"
#include <m3dia.hpp>

namespace squid
{

    class C_ProjectileAttack : public Component
    {
    public:
        C_ProjectileAttack(Object *owner);
        void Awake() override;
        void Start() override;
        void Update(float deltaTime) override;
        int classType() override;

    private:
        std::shared_ptr<C_Animation> animation;
        int projectileTextureID;

        void SpawnProjectile();

        std::shared_ptr<C_Direction> direction;
    };

} // namespace squid