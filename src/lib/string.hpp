#pragma once
#include "types.hpp"

namespace milk {
    constexpr void memset(byte_t* dst, byte_t value, size_t size);
    template <typename _type> constexpr void memcpy(const _type* src, _type* dst, size_t n);
} // namespace milk

extern "C" {
void _interop_memset(byte_t* dst, byte_t value, size_t size);
void _interop_memcpy(const byte_t* src, byte_t* dst, size_t size);
}

namespace milk {
    constexpr void memset(byte_t* dst, byte_t value, size_t size) {
        _interop_memset(dst, value, size);
    }

    template <typename _type> constexpr void memcpy(const _type* src, _type* dst, size_t n) {
        _interop_memcpy(reinterpret_cast<const byte_t*>(src), reinterpret_cast<byte_t*>(dst), n * sizeof(_type));
    }
} // namespace milk