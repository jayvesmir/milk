#pragma once
#include "lib/concepts.hpp"
#include "types.hpp"

namespace drivers {
    namespace serial {
        namespace uart {
            void init(ptr_t base);

            milk::optional<byte_t> read_byte();
            void write_byte(byte_t data);
            size_t write(const byte_t* data, size_t size);
        } // namespace uart
    } // namespace serial
} // namespace drivers

namespace drivers {
    namespace serial {
        namespace uart {
            template <typename _type> constexpr auto write(const _type* data, size_t n) {
                return write(reinterpret_cast<const byte_t*>(data), n * sizeof(_type));
            }

            template <milk::t8s _type> constexpr auto write_byte(const _type data) {
                return write_byte(static_cast<byte_t>(data));
            }

            template <milk::t8s _type> constexpr auto read_byte() {
                auto _ = read_byte();
                return _.has_value() ? milk::optional<_type>(_.value()) : milk::optional<_type>();
            }
        } // namespace uart
    } // namespace serial
} // namespace drivers