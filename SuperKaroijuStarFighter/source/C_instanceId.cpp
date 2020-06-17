#include "C_instanceId.hpp"

namespace squid
{
    int C_InstanceID::count = 0;

    C_InstanceID::C_InstanceID(Object *owner)
        : Component(owner),
          id(count++)
    {
    }

    C_InstanceID::~C_InstanceID() {}

    int C_InstanceID::Get() const
    {
        return id;
    }

    int C_InstanceID::classType()
    {
        return C_INSTANCEID;
    }
} // namespace squid