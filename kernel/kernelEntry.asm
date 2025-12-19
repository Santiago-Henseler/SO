bits 32
global kernelEntry

extern main

kernelEntry:
    ; Seteo los segmentos de datos
    mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

    mov esp, 0x90000 ; Espacio para el stack
    mov ebp, esp

    call main
    hlt