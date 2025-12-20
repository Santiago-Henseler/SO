ENTRY(kernelEntry)

SECTIONS {
    . = 0x00100000;

    .text : { *(.text*) }
    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .bss : { *(COMMON) *(.bss*) }

    . = ALIGN(16);
    stack_bottom = .;
    . += 16384;
    stack_top = .;
}