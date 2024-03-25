#pragma once
#include "types.hpp"

namespace milk {
    template <typename _type>
    concept t8s = requires { sizeof(_type) == 1; };
    template <typename _type>
    concept t16s = requires { sizeof(_type) == 2; };
    template <typename _type>
    concept t32s = requires { sizeof(_type) == 4; };
    template <typename _type>
    concept t64s = requires { sizeof(_type) == 8; };
} // namespace milk