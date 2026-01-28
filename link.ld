ENTRY(kernelEntry)

SECTIONS {
    . = 0x10000;
    
    kernelStart = .;

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

    .bss : {
        *(COMMON)
        *(.bss*)
        . = ALIGN(16);
        stack_bottom = .;
        . += 16384;
        stack_top = .;
    }

    . = ALIGN(16);
    kernelEnd = .;
}