#include "uart.hpp"
#include "config.hpp"

namespace drivers {
    namespace serial {
        namespace uart {
            u8 *receiver, *transmitter, *ier, *iir, *fifo_control, *line_control, *modem_control, *line_status,
                *modem_status;

            void init(ptr_t base) {
                ier           = reinterpret_cast<u8*>(base + 1);
                iir           = reinterpret_cast<u8*>(base + 2);
                receiver      = reinterpret_cast<u8*>(base);
                transmitter   = reinterpret_cast<u8*>(base);
                fifo_control  = reinterpret_cast<u8*>(base + 2);
                line_control  = reinterpret_cast<u8*>(base + 3);
                modem_control = reinterpret_cast<u8*>(base + 4);
                line_status   = reinterpret_cast<u8*>(base + 5);
                modem_status  = reinterpret_cast<u8*>(base + 6);

                *ier          = (1 << 0); // enable data interrupts
                *fifo_control = (1 << 0); // enable FIFO
                *line_control = (1 << 0) | (1 << 1); // word size 8

                // TODO: setup baud rate
            }

            milk::optional<byte_t> read_byte() {
                if (*line_status & 1)
                    return *receiver;
                return {};
            }

            void write_byte(byte_t data) {
                *transmitter = data;
            }

            size_t write(const byte_t* data, size_t size) {
                for (auto it = data; it < data + size; it++)
                    write_byte(*it);
                return size;
            }
        } // namespace uart
    } // namespace serial
} // namespace drivers