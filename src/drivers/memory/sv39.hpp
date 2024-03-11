#pragma once
#include "types.hpp"

namespace drivers {
    namespace sv39 {
        enum page_table_entry_flags {
            PTEF_valid    = (1 << 0),
            PTEF_read     = (1 << 1),
            PTEF_write    = (1 << 2),
            PTEF_execute  = (1 << 3),
            PTEF_user     = (1 << 4),
            PTEF_global   = (1 << 5),
            PTEF_accessed = (1 << 6),
            PTEF_dirty    = (1 << 7),

            PTEF_RW  = PTEF_read | PTEF_write,
            PTEF_RX  = PTEF_read | PTEF_execute,
            PTEF_RWX = PTEF_read | PTEF_write | PTEF_execute,

            PTEF_URW  = PTEF_user | PTEF_read | PTEF_write,
            PTEF_URX  = PTEF_user | PTEF_read | PTEF_execute,
            PTEF_URWX = PTEF_user | PTEF_read | PTEF_write | PTEF_execute,
        };

        class page_table_entry {
            u64 _bits;

          public:
            page_table_entry() {}
            page_table_entry(u64 bits) : _bits(bits) {}

            constexpr auto bits() const { return _bits; }
            constexpr auto set(u64 bits) { return (_bits = bits); }
            constexpr auto valid() const { return (_bits & PTEF_valid) == 1; }
            constexpr auto terminal() const { return (_bits & PTEF_RWX) != 0; }
        };

        class page_table {
            page_table_entry _entries[512];

          public:
            constexpr auto entries() const { return _entries; }

            constexpr auto& operator[](size_t index) { return _entries[index]; }
            constexpr auto& operator[](size_t index) const { return _entries[index]; }
        };

        extern page_table global_page_table;

        void init();

        void map(page_table& table, ptr_t paddr, ptr_t vaddr, page_table_entry_flags flags, size_t level);
    } // namespace sv39
} // namespace drivers