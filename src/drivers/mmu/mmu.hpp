#pragma once
#include "types.hpp"

namespace drivers {
    namespace mmu {
        extern size_t usable_memory_size;
        extern ptr_t memory_start, memory_end, data_start;

        void init(ptr_t memory_start_addr, ptr_t memory_end_addr);

        byte_t* allocate_pages(size_t n);
        void deallocate_pages(byte_t* ptr);
    } // namespace mmu
} // namespace drivers