#pragma once

#include "component.hpp"

namespace squid
{
    class C_InstanceID : public Component
    {
    public:
        C_InstanceID(Object *owner);
        ~C_InstanceID();

        unsigned Get() const;

        int classType() override;

    private:
        static unsigned int count;
        unsigned int id;
    };
} // namespace squid