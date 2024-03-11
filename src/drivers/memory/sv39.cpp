#include "sv39.hpp"
#include "config.hpp"
#include "lib/string.hpp"
#include "lib/utility.hpp"
#include "mmu.hpp"

namespace drivers {
    namespace sv39 {
        page_table global_page_table;

        void init() {
            milk::memset(&global_page_table, 0, 1);
        }

        void map(page_table& l2, ptr_t paddr, ptr_t vaddr, page_table_entry_flags flags, size_t level) {
            milk::fatal_assert(level <= 1);

            ptr_t vpn[3] = {
                (vaddr >> 12) & milk::bit_fill(9),
                (vaddr >> 21) & milk::bit_fill(9),
                (vaddr >> 30) & milk::bit_fill(9),
            };

            ptr_t ppn[3] = {
                (paddr >> 12) & milk::bit_fill(9),
                (paddr >> 21) & milk::bit_fill(9),
                (paddr >> 30) & milk::bit_fill(26),
            };

            auto* current_page = &l2[vpn[2]];

            for (auto i = 1ll; i >= static_cast<s64>(level); i--) {
                if (!current_page->valid()) {
                    auto p        = milk::memset(mmu::allocate_pages(1), 0, config::memory::page_size);
                    *current_page = (reinterpret_cast<ptr_t>(p) >> 2) | PTEF_valid;
                }

                current_page =
                    &reinterpret_cast<page_table_entry*>((current_page->bits() & ~milk::bit_fill(10ull)) << 2)[vpn[i]];
            }

            *current_page = (ppn[2] << 28ull) | (ppn[1] << 19ull) | (ppn[0] << 10ull) | flags | PTEF_valid;
        }
    } // namespace sv39
} // namespace drivers