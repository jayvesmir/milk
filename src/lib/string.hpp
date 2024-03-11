#pragma once
#include "interop.hpp"
#include "types.hpp"

namespace milk {
    constexpr auto memset(auto* dst, byte_t value, size_t n);
    template <typename _type> constexpr auto memcpy(const _type* src, _type* dst, size_t n);
} // namespace milk

namespace milk {
    constexpr auto memset(auto* dst, byte_t value, size_t n) {
        _interop_memset(reinterpret_cast<byte_t*>(dst), value, n * sizeof(*dst));
        return dst;
    }

    constexpr auto memcpy(const auto* src, auto* dst, size_t n) {
        _interop_memcpy(reinterpret_cast<const byte_t*>(src), reinterpret_cast<byte_t*>(dst), n * sizeof(*src));
        return dst;
    }
} // namespace milk