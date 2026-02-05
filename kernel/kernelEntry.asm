bits 32
global kernelEntry

extern main
extern stack_top

memRamSize equ 0x9000

kernelEntry:

    mov esp, stack_top ; Espacio del stack
    mov ebp, esp

    mov eax, [memRamSize]
    push eax
    call main
    hlt