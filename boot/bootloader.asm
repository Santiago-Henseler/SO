org 0x7c00                  ; Dirección del PC donde salta la BIOS al terminar
bits 16                     ; Modo real del procesador

start:  
    cli                     ; Bloqueo las interrupciones
    cld
    call loadKernel   
    lgdt [GDT]              ; Carga la GDT 
    jmp  changeMode
    hlt

loadKernel:
    mov  ax, 0x10            ; A donde voy a levantar en ram el sector leido
    mov  es, ax
    xor  bx, bx
 
    mov  ah, 02h             ; Indico que quiero leer un sector del disco
    mov  al, 20              ; Cantidad de Sectores
    mov  ch, 0
    mov  cl, 2               ; Sector del disco a leer
    mov  dh, 0
    mov  dl, 0
    int  13h                 ; Interrupcion para servicios de disco de bios
    jc   error
    mov  si, diskOk
    call  printBios
    ret 

error:
    mov si, errorMsg
    call printBios
    hlt

changeMode:
    mov  eax, cr0
    or   eax, 1
    mov  cr0, eax             ; Seteo el modo de 32 bits 
    jmp  GDT_code - GDT_start:0x00000100 ; Salto al inicio del segmento de codigo

%include "printBios.asm"

;;;Global Descriptor Table definicion;;;
GDT:
    dw GDT_end - GDT_start - 1
    dd GDT_start
GDT_start:
    GDT_null:
        dq 0x0000000000000000
    GDT_code:               ; Base + Limite + Flags del segmento de codigo
        dq 0x00CF9A000000FFFF
    GDT_data:               ; Base + Limite + Flags del segmento de data
        dq 0x00CF92000000FFFF
GDT_end:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

errorMsg: db "[Error] Hubo un problema al cargar el kernel", 0Dh, 0Ah, 0
diskOk:   db "[Info] Se cargo el kernel correctamente", 0Dh, 0Ah, 0

times 510 - ($-$$) db 0     ; Agrega la cantidad de 0 necesaria para completar el sector de disco 

dw 0xAA55                   ; Indica a la bios que es el boot