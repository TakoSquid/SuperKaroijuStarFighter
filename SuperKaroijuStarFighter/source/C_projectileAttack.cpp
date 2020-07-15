#include "C_projectileAttack.hpp"

#include "Object.hpp"

namespace squid
{
    C_ProjectileAttack::C_ProjectileAttack(Object *owner) : Component(owner)
    {
    }

    void C_ProjectileAttack::Awake()
    {
        animation = owner_->GetComponent<C_Animation>();
        direction = owner_->GetComponent<C_Direction>();
    }

    void C_ProjectileAttack::Start()
    {
        projectileTextureID = 16;
        owner_->context->spriteAllocator->getSprite(projectileTextureID);

        animation->AddAnimationAction(AnimationState::Casting, FacingDirection::None, 2, std::bind(&C_ProjectileAttack::SpawnProjectile, this));
    }

    void C_ProjectileAttack::Update(float deltaTime)
    {
        if (m3d::buttons::buttonPressed(m3d::buttons::A))
        {
            animation->SetAnimationState(AnimationState::Casting);
        }
        else if (m3d::buttons::buttonReleased(m3d::buttons::A))
        {
            animation->SetAnimationState(AnimationState::Idle);
        }
    }

    int C_ProjectileAttack::classType()
    {
        return C_PROJECTILEATTACK;
    }

    void C_ProjectileAttack::SpawnProjectile()
    {
        std::shared_ptr<Object> projectile = std::make_shared<Object>(owner_->context);
        projectile->transform->SetAngle(-90);

        FacingDirection currentDir = direction->Get();

        projectile->transform->SetPosition(owner_->transform->GetPosition());

        auto projSprite = projectile->AddComponent<C_Sprite>();
        projSprite->Load(projectileTextureID);
        projectile->SetSortOrder(100);

        auto vel = projectile->AddComponent<C_Velocity>();
        vel->Set(m3d::Vector2f{1.0f, 0.0f} * 500.0f);

        auto collider = projectile->AddComponent<C_BoxCollider>();
        collider->SetCollidable(m3d::BoundingBox{0, 0, 14, 8});
        collider->SetLayer(CollisionLayer::Projectile);

        projectile->AddComponent<C_RemoveObjectOnCollisionEnter>();

        owner_->context->objects->Add(projectile);
    }
} // namespace squid