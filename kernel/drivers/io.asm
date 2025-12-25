; Manda 1 byte al puerto I/O indicado 
global outB
outB:                   
    mov al, [esp + 8]       ; 1 Byte 
    mov dx, [esp + 4]       ; Puerto I/O
    out dx, al              ; Lo envia
    ret

; Recibe 1 byte del puerto I/O indicado
global inB
inB:
    mov dx, [esp + 4]       ; Puerto I/O
    in  al, dx
    ret