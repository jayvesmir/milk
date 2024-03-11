#pragma once
#include "types.hpp"

namespace drivers {
    namespace mmu {
        enum page_flags : u8 {
            PF_free = (0 << 0),
            PF_used = (1 << 0),
            PF_last = (1 << 1),
        };

        class page_t {
            u8 _flags;

          public:
            page_t() : _flags(PF_free) {}

            constexpr auto reset() { _flags = PF_free; }
            constexpr auto add_flag(page_flags flag) { _flags |= flag; }
            constexpr auto flags() { return static_cast<page_flags>(_flags); }

            constexpr auto free() { return _flags == PF_free; }
            constexpr auto used() { return _flags & PF_used; }
            constexpr auto last() { return _flags & PF_last; }

            constexpr auto operator|=(page_flags flag) { add_flag(flag); }
            constexpr auto operator|(page_flags flag) const { return _flags | flag; }
        };
    } // namespace mmu
} // namespace drivers