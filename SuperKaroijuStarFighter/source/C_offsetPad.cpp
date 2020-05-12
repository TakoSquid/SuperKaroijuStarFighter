#include "C_offsetPad.hpp"

namespace squid
{
C_OffsetPad::C_OffsetPad(Object *owner)
    : Component(owner)
{
}

int C_OffsetPad::classType()
{
    return C_OFFSETPAD;
}
} // namespace squid