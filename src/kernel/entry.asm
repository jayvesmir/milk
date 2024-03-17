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
    la gp, _interop_global_pointer
.option pop

    # kill all except the first hart
    csrr a0, mhartid
    bnez a0, _entry.failure

    csrw satp, zero
    
    # setup stack
    la a0, _interop_config_stack_end
    ld sp, (a0)

    jal clear_bss

    # load trap vectors
    la a0, _machine_trap
    la a1, _supervisor_trap
    csrw mtvec, a0
    csrw stvec, a1

    # set MPP to machine mode
    li a0, (3 << 11)
    csrr a1, mstatus
    or a0, a0, a1
    csrw mstatus, a0

    # mret will jump to boot()
    la a0, boot
    csrw mepc, a0

    # boot() will return to _entry.ssetup
    la ra, _entry.ssetup

    mret

_entry.ssetup:
    # boot() returns the level 2 page table PPN
    mv t0, a0

    # set MPP to machine mode
    li a0, (3 << 11)
    csrr a1, mstatus
    or a0, a0, a1
    csrw mstatus, a0

    # mret will jump to kernel_main()
    la a0, kernel_main
    csrw mepc, a0

    # set sv39 paging mode
    li a1, (8 << 60)
    or a0, t0, a1
    csrw satp, t0

    # TODO: jump into kernel_main() in supervisor mode,
    # my mind is kidna getting fucked up by PMP so fuck you, no supervisor mode for you 
    mret

_entry.failure:
    j _die