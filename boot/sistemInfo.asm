getMemSize:
    xor  ax, ax
    mov  es, ax
    mov  di, buffer      ; Seteo la direccion donde escribir el struct

    xor  ebx, ebx        ; Primer iteración en 0

    xor  ebp, ebp        ; Lo uso de acumulador
    
    .loop:
        mov  eax, 0xE820        ; Parametro de la interrupcion
        mov  edx, 'SMAP'
        mov  ecx, 24            ; Tamaño del buffer   
        int  15h                ; Interrupcion para detectar mem en bios
        jc   .error
        cmp eax, 'SMAP'
        jne .error
        ; Soporto maximo 4GB de ram 
        cmp  dword [buffer+12], 0
        jne   .moreRam
        ; Si no es usable la paso 
        cmp dword [buffer + 16], 1
        jne .next
        ; Sumo el tamaño del bloque de memoria
        add  ebp, [buffer+8]    
        ; Si ebx es 0 recorri todos los bloques
        cmp  ebx, 0
        je   .end
        .next:
            jmp .loop
    .moreRam:
        mov si, warningMsgRam
        call printBios
        jmp .end
    .error:
        mov si, errorMsgRam
        call printBios
        hlt
    .end:
        mov  [memSize], ebp
        ret      

errorMsgRam: db "[Error] Hubo un problema al leer toda la memoria ram", 0Dh, 0Ah, 0
warningMsgRam: db "[Info] El kernel solo va a soportar 4GB de ram, el resto no sera utilizado", 0Dh, 0Ah, 0

buffer equ 0x0500