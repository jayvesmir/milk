#include "config.hpp"
#include "drivers.hpp"

extern "C" {
void clear_bss() {
    extern byte_t *_interop_bss_start, *_interop_bss_end;
    for (auto it = &_interop_bss_start; it < &_interop_bss_end; it++)
        *reinterpret_cast<byte_t*>(it) = 0;
}

void uart_console() {
    using namespace drivers::serial;

    uart::write("milk> ", 7);
    while (true) {
        auto byte = uart::read_byte();
        if (byte.has_value()) {
            switch (byte.value()) {
            case 8:
            case 127:
                uart::write_byte(8);
                uart::write_byte(' ');
                uart::write_byte(8);
                break;
            case 13:
            case '\n':
                uart::write_byte('\n');
                break;
            default:
                uart::write_byte(byte.value());
                break;
            }
        }
    }
}

void boot() {
    extern byte_t *_interop_bss_start, *_interop_bss_end;

    clear_bss();
    drivers::serial::uart::init(config::uart::base);

    uart_console();

    return;
}
}