#include "sv39.hpp"
#include "config.hpp"
#include "lib/string.hpp"
#include "mmu.hpp"

namespace drivers {
    namespace sv39 {
        page_table global_page_table;

        template <> address<AT_physical>::address(ptr_t addr) {
            _data[0] = (addr >> 12) & milk::bit_fill(9);
            _data[1] = (addr >> 21) & milk::bit_fill(9);
            _data[2] = (addr >> 30) & milk::bit_fill(26);
        }

        template <> address<AT_virtual>::address(ptr_t addr) {
            _data[0] = (addr >> 12) & milk::bit_fill(9);
            _data[1] = (addr >> 21) & milk::bit_fill(9);
            _data[2] = (addr >> 30) & milk::bit_fill(9);
        }

        void init() {
            milk::memset(&global_page_table, 0, 1);
        }

        void map(ptr_t paddr, ptr_t vaddr, page_table_entry_flags flags, size_t level) {
            milk::fatal_assert(level <= 1);

            address<AT_virtual> vpn(vaddr);
            address<AT_physical> ppn(paddr);

            auto* entry = &global_page_table[vpn[2]];

            for (auto i = 1ll; i >= static_cast<s64>(level); i--) {
                if (!entry->valid()) {
                    auto p = milk::memset(mmu::allocate_pages(1), 0, config::memory::page_size);
                    *entry = (reinterpret_cast<ptr_t>(p) >> 2) | PTEF_valid;
                }

                entry = &reinterpret_cast<page_table_entry*>((entry->bits() & ~milk::bit_fill(10ull)) << 2)[vpn[i]];
            }

            *entry = (ppn[2] << 28ull) | (ppn[1] << 19ull) | (ppn[0] << 10ull) | flags | PTEF_valid;
        }

        void unmap() {
            for (auto i = 0; i < 512; i++) {
                if (global_page_table[i].valid() && !global_page_table[i].terminal()) {
                    auto addr_cache =
                        reinterpret_cast<page_table*>((global_page_table[i].bits() & ~milk::bit_fill(10ull)) << 2);
                    auto& l1_table = *addr_cache;
                    for (auto ii = 0; ii < 512; ii++) {
                        if (l1_table[ii].valid() && !l1_table[ii].terminal()) {
                            mmu::deallocate_pages(
                                reinterpret_cast<byte_t*>((l1_table[ii].bits() & ~milk::bit_fill(10ull)) << 2));
                            l1_table[ii].invalidate();
                        }
                    }
                    mmu::deallocate_pages(reinterpret_cast<byte_t*>(addr_cache));
                    global_page_table[i].invalidate();
                }
            }
        }

        milk::optional<ptr_t> physical_from_virtual(ptr_t vaddr) {
            address<AT_virtual> vpn(vaddr);
            auto* entry = &global_page_table[vpn[2]];

            for (auto i = 2ll; i >= 0; i--) {
                if (!entry->valid())
                    break;

                if (entry->terminal()) {
                    auto mask = (1 << (12 + i * 9)) - 1; // https://osblog.stephenmarz.com/ch3.2.html
                    return {((entry->bits() << 2) & ~mask) | (vaddr & mask)};
                }

                if (i == 0)
                    break;

                entry = &reinterpret_cast<page_table_entry*>((entry->bits() & ~milk::bit_fill(10ull)) << 2)[vpn[i - 1]];
            }

            return {};
        }
    } // namespace sv39
} // namespace drivers