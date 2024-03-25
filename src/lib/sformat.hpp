#pragma once
#include "drivers.hpp"
#include "stream.hpp"
#include "string.hpp"

namespace milk {
    template <typename _first_t, typename... _rest>
    constexpr auto sformat(basic_ostream<char>& stream, const char* fmt, const _first_t& first, const _rest&... rest);
    template <typename _type> constexpr auto sformat(basic_ostream<char>& stream, const _type& val);

    template <typename... _rest> constexpr auto print(const char* fmt, const _rest&... rest);
} // namespace milk

namespace milk {
    template <typename _type>
    constexpr auto sformat(basic_ostream<char>& stream [[maybe_unused]], const _type& val [[maybe_unused]]) {
        return;
    }

    template <milk::is_integral _type> constexpr auto sformat(basic_ostream<char>& stream, const _type& val) {
        if (val == 0) {
            stream.put('0');
            return;
        }

        auto copy = val;

        if (copy < 0) {
            stream.put('-');
            copy = -copy;
        }

        auto buf    = drivers::mmu::allocate<char>(256);
        auto cursor = 0;

        while (copy > 0) {
            buf[cursor++] = (copy % 10) + '0';
            copy /= 10;
        }

        for (auto i = cursor - 1; i >= 0; i--)
            stream.put(buf[i]);

        drivers::mmu::deallocate(buf);
    }

    template <> constexpr auto sformat<char>(basic_ostream<char>& stream, const char& val) {
        stream.put(val);
    }

    template <typename _type, size_t n> constexpr auto sformat(basic_ostream<char>& stream, const auto& val) {
        stream.write(val, n);
    }

    constexpr auto sformat(basic_ostream<char>& stream, const char* fmt) {
        stream.write(fmt, strlen(fmt));
    }

    template <typename _last_t>
    constexpr auto sformat(basic_ostream<char>& stream, const char* fmt, const _last_t& last) {
        while (*fmt) {
            if (*fmt == '%') {
                if (*(fmt + 1) == '%') {
                    stream.put('%');
                    fmt += 2;
                    continue;
                }
                sformat(stream, last);
            } else
                stream.put(*fmt);
            fmt++;
        }
    }

    template <typename _first_t, typename... _rest>
    constexpr auto sformat(basic_ostream<char>& stream, const char* fmt, const _first_t& first, const _rest&... rest) {
        while (*fmt) {
            if (*fmt == '%') {
                if (*(fmt + 1) == '%') {
                    stream.put('%');
                    fmt += 2;
                    continue;
                }
                sformat(stream, first);
                sformat(stream, ++fmt, rest...);
                break;
            } else
                stream.put(*fmt);
            fmt++;
        }
    }

    template <typename... _rest> constexpr auto print(const char* fmt, const _rest&... rest) {
        return sformat(serial_console, fmt, rest...);
    }
} // namespace milk