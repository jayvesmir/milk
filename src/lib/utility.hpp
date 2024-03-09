#pragma once

namespace milk {
    // aligns x to the nearest greater multiple of a
    constexpr auto align_up(auto x, auto a) {
        return (x + (a - 1)) & ~(a - 1);
    }

    // aligns x to the nearest lesser multiple of a
    constexpr auto align_down(auto x, auto a) {
        return x & ~(a - 1);
    }
} // namespace milk