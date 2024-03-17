#include "drivers.hpp"
#include "lib/interop.hpp"
#include "types.hpp"

extern "C" {
void _machine_trap() {
    ptr_t fault_addr = 0, cause = 0;
    asm volatile("csrr %0, mtval" : "=r"(fault_addr));
    asm volatile("csrr %0, mcause" : "=r"(cause));

    drivers::serial::uart::write("machine trap invoked\n", 22);

    _die();
}

void _supervisor_trap() {
    ptr_t fault_addr = 0, cause = 0;
    asm volatile("csrr %0, mtval" : "=r"(fault_addr));
    asm volatile("csrr %0, mcause" : "=r"(cause));

    drivers::serial::uart::write("supervisor trap invoked\n", 25);

    _die();
}
}