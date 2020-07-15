#include "C_removeObjectOnCollisionEnter.hpp"

#include "object.hpp"
#include "C_boxCollider.hpp"

namespace squid
{
    int C_RemoveObjectOnCollisionEnter::classType()
    {
        return C_REMOVEOBJECTONCOLLISIONENTER;
    }

    C_RemoveObjectOnCollisionEnter::C_RemoveObjectOnCollisionEnter(Object *owner) : Component(owner) {}

    void C_RemoveObjectOnCollisionEnter::OnCollisionEnter(std::shared_ptr<C_BoxCollider> other)
    {
        owner_->QueueForRemoval();

        std::cout << "Enter" << std::endl;
    }

    void C_RemoveObjectOnCollisionEnter::OnCollisionStay(std::shared_ptr<C_BoxCollider> other)
    {
        std::cout << "Stay" << std::endl;
    }

    void C_RemoveObjectOnCollisionEnter::OnCollisionExit(std::shared_ptr<C_BoxCollider> other)
    {
        std::cout << "Exit" << std::endl;
    }
} // namespace squid