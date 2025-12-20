global outB

; Manda 1 byte al puerto I/O indicado ;
outB:                   
    mov al, [esp + 8]       ; 1 Byte 
    mov dx, [esp + 4]       ; Puerto I/O
    out dx, al              ; Lo envia
    ret

