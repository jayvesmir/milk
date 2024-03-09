.section .text

# these could be vectorized, i dont think its worth it tho
.global _interop_memset
.global _interop_memcpy

# a0 = src, a1 = dst, a2 = size
_interop_memcpy:
    beqz a2, _interop_memcpy.exit

_interop_memcpy.loop:
    lb t0, (a0)
    sb t0, (a1)
    addi a0, a0, 1
    addi a1, a1, 1
    addi a2, a2, -1
    bnez a2, _interop_memcpy.loop
_interop_memcpy.exit:
    ret

# a0 = src, a1 = value, a2 = size
_interop_memset:
    beqz a2, _interop_memset.exit

_interop_memset.loop:
    sb a1, (a0)
    addi a0, a0, 1
    addi a2, a2, -1
    bnez a2, _interop_memset.loop
_interop_memset.exit:
    ret