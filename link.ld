ENTRY(kernelEntry)

SECTIONS {
    . = 0x10000;

    .text : {  
        kernelEntry.o(.text)
        *(.text*)
    }
    .rodata : { 
        *(.rodata*) 
    }
    .data : { 
        *(.data*) 
    }

    .bss (NOLOAD) : {
        *(COMMON)
        *(.bss*)
    }

    .stack (NOLOAD) : {
        . = ALIGN(16);
        stack_bottom = .;
        . += 16384;
        stack_top = .;
    }
}