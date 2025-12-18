bits 32

kernelEntry:
    ; Seteo los segmentos de datos
    mov ax, GDT_data - GDT_start
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax


    mov ebp, 0x90000
	mov esp, ebp

    mov al, 'A'
    mov ah, 0x0f
    mov [0xb8000], ax
    jmp $