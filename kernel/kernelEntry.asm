bits 32
global kernelEntry

extern stack_top
extern main

memSize equ 0x9000

kernelEntry:

    ; Seteo los segmentos de datos
    mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
    mov ss, ax

    mov esp, stack_top ; Espacio del stack
    mov ebp, esp
    
    mov eax, [memSize]
    push eax
    call main
    hlt