#include "lib/interop.hpp"
#include "lib/sformat.hpp"
#include "types.hpp"

extern "C" {
void _machine_trap() {
    ptr_t fault_addr = 0, cause = 0;
    asm volatile("csrr %0, mtval" : "=r"(fault_addr));
    asm volatile("csrr %0, mcause" : "=r"(cause));

    milk::print("machine trap invoked at % with the cause %\n", fault_addr, cause);

    _die();
}

void _supervisor_trap() {
    ptr_t fault_addr = 0, cause = 0;
    asm volatile("csrr %0, mtval" : "=r"(fault_addr));
    asm volatile("csrr %0, mcause" : "=r"(cause));

    milk::print("machine trap invoked at % with the cause %\n", fault_addr, cause);

    _die();
}
}