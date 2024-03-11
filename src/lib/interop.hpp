#pragma once
#include "types.hpp"

extern "C" {
void _die(void);

void _interop_memset(byte_t* dst, byte_t value, size_t size);
void _interop_memcpy(const byte_t* src, byte_t* dst, size_t size);
}