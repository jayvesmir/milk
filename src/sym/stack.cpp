#include "config.hpp"

namespace config {
    namespace stack {
        byte_t ptr[stack::size];

        byte_t* start = ptr;
        byte_t* end   = ptr + stack::size;
    } // namespace stack
} // namespace config

auto _interop_config_stack_size  = config::stack::size;
auto _interop_config_stack_start = config::stack::start;
auto _interop_config_stack_end   = config::stack::end;