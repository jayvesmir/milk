#pragma once
#include "config.hpp"
#include "lib/utility.hpp"
#include "types.hpp"

namespace drivers {
    namespace mmu {
        extern size_t usable_memory_size;
        extern ptr_t memory_start, memory_end, data_start;

        void init(ptr_t memory_start_addr, ptr_t memory_end_addr);

        byte_t* allocate_pages(size_t n);
        void deallocate_pages(byte_t* ptr);

        template <typename _type> constexpr auto allocate(size_t n);
        template <typename _type> constexpr auto deallocate(_type* ptr);
    } // namespace mmu
} // namespace drivers

namespace drivers {
    namespace mmu {
        template <typename _type> constexpr auto allocate(size_t n) {
            return reinterpret_cast<_type*>(allocate_pages(milk::clamp(
                1, usable_memory_size / config::memory::page_size, (n * sizeof(_type)) / config::memory::page_size)));
        }

        template <typename _type> constexpr auto deallocate(_type* ptr) {
            return deallocate_pages(reinterpret_cast<byte_t*>(ptr));
        }
    } // namespace mmu
} // namespace drivers