#pragma once

#include "squid/engine/component.hpp"

namespace squid
{
class C_OffsetPad : public Component
{
    C_OffsetPad(Object *owner);

    int classType();
};
} // namespace squid