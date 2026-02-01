bits 32
global kernelEntry

extern main
extern stack_top

memSize equ 0x9000

kernelEntry:

    mov esp, stack_top ; Espacio del stack
    mov ebp, esp

    mov eax, [memSize]
    push eax
    call main
    hlt