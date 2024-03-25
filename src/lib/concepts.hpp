#pragma once
#include "types.hpp"

namespace milk {
    namespace detail {
        template <typename _type> struct is_integral : milk::false_type {};
        template <> struct is_integral<bool> : milk::true_type {};
        template <> struct is_integral<char> : milk::true_type {};
        template <> struct is_integral<unsigned char> : milk::true_type {};
        template <> struct is_integral<short> : milk::true_type {};
        template <> struct is_integral<unsigned short> : milk::true_type {};
        template <> struct is_integral<int> : milk::true_type {};
        template <> struct is_integral<unsigned int> : milk::true_type {};
        template <> struct is_integral<long> : milk::true_type {};
        template <> struct is_integral<unsigned long> : milk::true_type {};
        template <> struct is_integral<long long> : milk::true_type {};
        template <> struct is_integral<unsigned long long> : milk::true_type {};
    } // namespace detail

    template <typename _type>
    concept t8s = requires { sizeof(_type) == 1; };
    template <typename _type>
    concept t16s = requires { sizeof(_type) == 2; };
    template <typename _type>
    concept t32s = requires { sizeof(_type) == 4; };
    template <typename _type>
    concept t64s = requires { sizeof(_type) == 8; };
    template <typename _type>
    concept t128s = requires { sizeof(_type) == 16; };

    template <typename _type>
    concept is_integral = requires { detail::is_integral<_type>::v == true; };
} // namespace milk