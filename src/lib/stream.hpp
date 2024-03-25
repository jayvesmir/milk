#pragma once
#include "drivers/serial/uart.hpp"
#include "types.hpp"

namespace milk {
    namespace detail {
        template <typename _type> using stream_getfn_t   = milk::optional<_type> (*)();
        template <typename _type> using stream_putfn_t   = void (*)(const _type&);
        template <typename _type> using stream_writefn_t = size_t (*)(const _type*, size_t);
    } // namespace detail

    enum data_direction { mdd_in, mdd_out, mdd_io };

    template <typename _type, data_direction _direction> struct basic_stream {};

    template <typename _type> struct basic_stream<_type, mdd_out> {
        detail::stream_putfn_t<_type> put;
        detail::stream_writefn_t<_type> write;
    };

    template <typename _type> struct basic_stream<_type, mdd_in> {
        detail::stream_getfn_t<_type> get;
    };

    template <typename _type>
    struct basic_stream<_type, mdd_io> : public basic_stream<_type, mdd_in>, public basic_stream<_type, mdd_out> {};

    template <typename _type> using basic_iostream = basic_stream<_type, mdd_io>;
    template <typename _type> using basic_istream  = basic_stream<_type, mdd_in>;
    template <typename _type> using basic_ostream  = basic_stream<_type, mdd_out>;

    extern basic_iostream<char> serial_console;
} // namespace milk