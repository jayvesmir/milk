#pragma once
#include "types.hpp"

namespace drivers {
    namespace power {
        void init(ptr_t test_addr);

        void reboot();
        void poweroff();
    } // namespace power
} // namespace drivers