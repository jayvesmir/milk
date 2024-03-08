.section .text

.global _die
_die:
    wfi
    j _die

.section .text.entry
.global _entry
_entry:
    .option push
    .option norelax
        la      gp, _interop_global_pointer
    .option pop

    # kill all except the first hart
    csrr a0, mhartid
    bne  a0, zero, _die

    # setup stack
    la sp, _interop_config_stack_end

_entry.boot:
    j boot
    j _die