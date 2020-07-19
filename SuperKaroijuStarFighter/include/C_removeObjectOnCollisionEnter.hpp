#pragma once

#include <string>

#include "component.hpp"
namespace squid
{
    class C_RemoveObjectOnCollisionEnter : public Component
    {
    public:
        int classType() override;

        C_RemoveObjectOnCollisionEnter(Object *owner);

        void OnCollisionEnter(std::shared_ptr<C_BoxCollider> other) override;
        void OnCollisionStay(std::shared_ptr<C_BoxCollider> other) override;
        void OnCollisionExit(std::shared_ptr<C_BoxCollider> other) override;
    };
} // namespace squid