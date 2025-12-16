org 0x7c00              ; Dirección del PC donde salta la BIOS al terminar
bits 16
start:  jmp boot

boot:
    cli                 ; Bloqueo las interrupciones
    cld
    jmp  loadSystem   
    hlt

loadSystem:
    mov ax, 0x10       ; A donde voy a levantar en ram el sector leido
    mov es, ax
    xor bx, bx

    mov ah, 02h         ; Indico que quiero leer un sector del disco
    mov al, 1           ; Cantidad de Sectores
    mov ch, 0
    mov cl, 2           ; Sector del disco a leer
    mov dh, 0
    mov dl, 0
    int 13h             ; Interrupcion para servicios de disco de bios
    jc  error
    jmp  0x10:0x0       ; Salto lejano
    ret 

error:
    hlt

times 510 - ($-$$) db 0

dw 0xAA55               ; Indica a la bios que es el boot