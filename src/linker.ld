OUTPUT_ARCH(riscv)
ENTRY(_entry)

MEMORY {
    ram (RWX) : ORIGIN = 0x80000000, LENGTH = 256M
}

PHDRS {
  text PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
}

SECTIONS {
    .text : ALIGN(4K) { 
        _interop_text_start = .;
        *(.text.entry) *(.text) *(.text.*)
        _interop_text_end = .;
    } > ram AT > ram :text

    _interop_global_pointer = .;

    .data : ALIGN(4K) {
        _interop_data_start = .;
        *(.data) *(.data.*)
        *(.sdata) *(.sdata.*)
        _interop_data_end = .;
    } > ram AT > ram :data

    .rodata : ALIGN(4K) {
        _interop_rodata_start = .;
        *(.rodata) *(.rodata.*)
        *(.srodata) *(.srodata.*)
        _interop_rodata_end = .;
    } > ram AT > ram :data

    .bss : ALIGN(4K) {
        _interop_bss_start = .;
        *(.bss) *(.bss.*)
        *(.sbss) *(.sbss.*)
        . = ALIGN(8);
        _interop_bss_end = .;
    } > ram AT > ram :bss

    . = ALIGN(4K);

    _interop_memory_start = .;
    _interop_memory_end = ORIGIN(ram) + LENGTH(ram);
}