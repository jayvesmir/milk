OUTPUT_ARCH(riscv)
ENTRY(_entry)

MEMORY {
    ram (rwx) : ORIGIN = 0x80000000, LENGTH = 256M
}

PHDRS {
  text PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
}

SECTIONS {
    .text : ALIGN(4K) { 
        *(.text.entry) *(.text)
    } >ram AT>ram :text

    PROVIDE(_interop_global_pointer = .);

    .data : ALIGN(4K) {
        *(.data) *(.sdata)
    } >ram AT>ram :data

    .bss : ALIGN(4K) {
        PROVIDE(_interop_bss_start = .);
        *(.bss) *(.sbss)
        PROVIDE(_interop_bss_end = .);
    } >ram AT>ram :bss
}