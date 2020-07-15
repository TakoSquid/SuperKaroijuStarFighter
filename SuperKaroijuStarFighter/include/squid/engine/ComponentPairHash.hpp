#pragma once

#include <cstddef>

namespace squid
{
    struct ComponentPairHash
    {
        template <typename T>
        std::size_t operator()(T t) const
        {
            std::size_t x = t.first->owner_->instanceID->Get();
            std::size_t y = t.second->owner_->instanceID->Get();

            return (x >= y) ? (x * x + x + y) : (y * y + y + x);
        }
    };

} // namespace squid