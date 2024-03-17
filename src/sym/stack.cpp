#include "config.hpp"

namespace config {
    namespace stack {
        byte_t start[stack::size];

        byte_t* end = start + stack::size;
    } // namespace stack
} // namespace config

auto _interop_config_stack_size  = config::stack::size;
auto _interop_config_stack_start = config::stack::start;
auto _interop_config_stack_end   = config::stack::end;