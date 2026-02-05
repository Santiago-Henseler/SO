; struct structRamInfo{
;       uint64 addrBase;
;       uint64 lenght;
;       uint32 type;
;       uint32 extAttr;
;}
structRamInfo equ 0x500

getMemRamSize:
    xor  ax, ax
    mov  es, ax
    mov  di, structRamInfo      ; Seteo la direccion donde escribir el struct

    xor  ebx, ebx        ; Primer iteración en 0
    xor  ebp, ebp        ; Lo uso de acumulador
    mov  [memRamSize], ebp  ; Seteo donde voy a guardar el resultado en 0

    .loop:
        mov  eax, 0xE820         ; Parametro de la interrupcion
        mov  edx, 0x534D4150     ; Seteo el magic number
        mov  ecx, 24             ; Tamaño del structRamInfo   
        int  15h                 ; Interrupcion para detectar mem en bios
        
        jc   .error
        cmp  eax, 0x534D4150
        jne  .error
        
        cmp  ebx, 0              ; Si ebx es 0 recorri todos los bloques
        je   .end

        cmp  dword [structRamInfo+12], 0 ; Soporto maximo 4GB de ram (tamaño de bloque entra en 32 bits)
        jne  .moreRam

        cmp  dword [structRamInfo+16], 1  ; Si no es usable no la sumo
        jne  .next

        cmp  dword [structRamInfo], 0x100000 ; Si estoy antes que el kernel no lo sumo
        jb  .next
        
        add  ebp, [structRamInfo+8]      ; Sumo el tamaño del bloque de memoria
        .next:
            jmp .loop

    .moreRam:
        mov  si, warningMsgRam
        call printBios
        jmp  .end
    .error:
        mov  si, errorMsgRam
        call printBios
        hlt
    .end:
        mov  [memRamSize], ebp
        ret      

errorMsgRam: db "[Error] Hubo un problema al leer toda la memoria ram", 0Dh, 0Ah, 0
warningMsgRam: db "[Info] El kernel solo va a soportar 4GB de ram, el resto no sera utilizado", 0Dh, 0Ah, 0