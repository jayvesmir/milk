#pragma once
#include "types.hpp"

namespace drivers {
    namespace serial {
        namespace uart {
            void init(ptr_t base);

            milk::optional<byte_t> read_byte();
            void write_byte(byte_t data);
            void write(const byte_t* data, size_t size);
        } // namespace uart
    } // namespace serial
} // namespace drivers

namespace drivers {
    namespace serial {
        namespace uart {
            template <typename _type> constexpr void write(const _type* data, size_t size) {
                write(reinterpret_cast<const byte_t*>(data), size);
            }
        } // namespace uart
    } // namespace serial
} // namespace drivers