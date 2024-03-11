#include "config.hpp"
#include "lib/utility.hpp"
#include "mmu.hpp"
#include "page.hpp"

namespace drivers {
    namespace mmu {
        byte_t* allocate_pages(size_t n) {
            auto max_page =
                reinterpret_cast<page_t*>(memory_start + (usable_memory_size / config::memory::page_size)) - n;

            if (n > (usable_memory_size / config::memory::page_size))
                return nullptr;

            for (auto it = reinterpret_cast<page_t*>(memory_start); it < max_page; it++) {
                if (it->used())
                    continue;

                page_t* page_ptr = it;

                for (auto _ = 1ull; _ < n; _++) {
                    if (it[_].used()) {
                        page_ptr = nullptr;
                        break;
                    }
                }

                if (!page_ptr)
                    continue;

                for (auto _ = 0ull; _ < n; _++)
                    it[_] |= PF_used;
                it[n - 1] |= PF_last;

                volatile auto _ = (page_ptr - reinterpret_cast<page_t*>(memory_start)) * config::memory::page_size;
                return reinterpret_cast<byte_t*>(data_start + _);
            }

            return nullptr;
        }

        void deallocate_pages(byte_t* ptr) {
            auto page = reinterpret_cast<page_t*>(memory_start + reinterpret_cast<ptr_t>(ptr - data_start) /
                                                                     config::memory::page_size);

            while (!page->last() && page->used())
                page++->reset();
            page->reset();
        }
    } // namespace mmu
} // namespace drivers