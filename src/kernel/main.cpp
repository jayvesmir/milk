#include "config.hpp"
#include "drivers.hpp"
#include "lib/stream.hpp"

extern "C" {
void clear_bss() {
    extern u64 *_interop_bss_start, *_interop_bss_end;
    for (auto it = &_interop_bss_start; it < &_interop_bss_end; it++)
        *reinterpret_cast<u64*>(it) = 0;
}

void kernel_main() {
    using namespace drivers::serial;

    milk::serial_console.write("milk> ", 7);
    while (true) {
        auto byte = milk::serial_console.get();
        if (!byte.has_value())
            continue;

        switch (byte.value()) {
        case 8:
        case 127:
            milk::serial_console.put(8);
            milk::serial_console.put(' ');
            milk::serial_console.put(8);
            break;
        case 13:
            milk::serial_console.put('\n');
            break;
        default:
            milk::serial_console.put(byte.value());
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