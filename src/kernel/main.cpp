#include "config.hpp"
#include "drivers.hpp"

extern "C" {
void clear_bss() {
    extern u64 *_interop_bss_start, *_interop_bss_end;
    for (auto it = &_interop_bss_start; it < &_interop_bss_end; it++)
        *reinterpret_cast<u64*>(it) = 0;
}

void kernel_main() {
    using namespace drivers::serial;

    uart::write("milk> ", 7);
    while (true) {
        auto byte = uart::read_byte();
        if (!byte.has_value())
            continue;

        switch (byte.value()) {
        case 8:
        case 127:
            uart::write_byte(8);
            uart::write_byte(' ');
            uart::write_byte(8);
            break;
        case 13:
            uart::write_byte('\n');
            break;
        default:
            uart::write_byte(byte.value());
            break;
        }
    }

    drivers::sv39::unmap();
    drivers::power::poweroff();
}

u64 boot() {
    drivers::power::init(config::test::base);
    drivers::serial::uart::init(config::uart::base);
    drivers::mmu::init(config::memory::start, config::memory::end);

    auto root_ppn = drivers::sv39::address<drivers::sv39::AT_physical>(
                        reinterpret_cast<ptr_t>(drivers::sv39::global_page_table.entries()))
                        .pack_ppn();

    return root_ppn >> 2;
}
}