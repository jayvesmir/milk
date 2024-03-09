#include "power.hpp"

namespace drivers {
    namespace power {
        u16* test;

        void init(ptr_t test_addr) {
            test = reinterpret_cast<u16*>(test_addr);
        }

        void reboot() {
            *test = 0x7777;
        }

        void poweroff() {
            *test = 0x5555;
        }
    } // namespace power
} // namespace drivers