#pragma once
#include "interop.hpp"

namespace milk {
    // aligns x to the nearest greater multiple of a
    constexpr auto align_up(auto x, auto a) {
        return (x + (a - 1)) & ~(a - 1);
    }

    // aligns x to the nearest lesser multiple of a
    constexpr auto align_down(auto x, auto a) {
        return x & ~(a - 1);
    }

    // returns a number that has n bits set to 1
    // n = 9 -> 511
    constexpr auto bit_fill(auto n) {
        return (decltype(n)(1) << n) - decltype(n)(1);
    }

    // kills the system if p is false
    constexpr auto fatal_assert(auto p) {
        if (!p)
            _die();
    }

    // clamps v between min and max
    constexpr auto clamp(const auto& min, const auto& max, const auto& v) {
        return v < min ? min : v > max ? max : v;
    }
} // namespace milk