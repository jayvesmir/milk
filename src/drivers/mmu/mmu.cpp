#include "mmu.hpp"
#include "config.hpp"
#include "lib/utility.hpp"
#include "page.hpp"

namespace drivers {
    namespace mmu {
        size_t usable_memory_size;
        ptr_t memory_start, memory_end, data_start;

        void init(ptr_t memory_start_addr, ptr_t memory_end_addr) {
            memory_start = memory_start_addr;
            memory_end   = memory_end_addr;
            data_start   = milk::align_up(memory_start + ((memory_end - memory_start) / config::memory::page_size),
                                          config::memory::page_size);
            usable_memory_size = (memory_end - data_start);

            // clear all page bits
            for (auto it = reinterpret_cast<page_t*>(memory_start); it < reinterpret_cast<page_t*>(data_start); it++)
                it->reset();
        }
    } // namespace mmu
} // namespace drivers