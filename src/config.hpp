#pragma once
#include "types.hpp"

#define MACHINE_QEMU_VIRT 1
extern ptr_t _interop_memory_start;
extern ptr_t _interop_memory_end;

namespace config {
    namespace stack {
        extern byte_t *start, *end;
        static constexpr size_t size = 16'384;
    } // namespace stack

    namespace memory {
        static constexpr size_t page_size = 4096;

        static ptr_t start = reinterpret_cast<ptr_t>(&_interop_memory_start);
        static ptr_t end   = reinterpret_cast<ptr_t>(&_interop_memory_end);
    } // namespace memory

#if MACHINE_QEMU_VIRT
    namespace uart {
        static constexpr ptr_t base = 0x10000000;
    }

    namespace test {
        static constexpr ptr_t base = 0x100000;
    }
#endif
} // namespace config