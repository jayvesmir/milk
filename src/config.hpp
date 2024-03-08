#pragma once
#include "types.hpp"

#define MACHINE_QEMU_VIRT 1

namespace config {
    namespace stack {
        extern byte_t *start, *end;
        constexpr size_t size = 16'384;
    } // namespace stack

#if MACHINE_QEMU_VIRT
    namespace uart {
        constexpr ptr_t base = 0x10000000;
    }
#endif
} // namespace config