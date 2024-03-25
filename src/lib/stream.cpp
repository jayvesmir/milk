#include "stream.hpp"

namespace milk {
    auto serial_console = basic_iostream<char>{{drivers::serial::uart::read_byte<char>},
                                               {drivers::serial::uart::write_byte, drivers::serial::uart::write}};
}