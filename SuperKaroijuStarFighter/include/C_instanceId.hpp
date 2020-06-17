#pragma once

#include "component.hpp"

namespace squid
{
    class C_InstanceID : public Component
    {
    public:
        C_InstanceID(Object *owner);
        ~C_InstanceID();

        int Get() const;

        int classType() override;

    private:
        static int count;
        int id;
    };
} // namespace squid