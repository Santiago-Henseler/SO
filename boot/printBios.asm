; Pasar la direccion de lo que se va a printear en si 
printBios:
    .loop:             
        mov  al, [si]       ; Guardo en al lo que voy a escribir en terminal
        cmp  al, 0          
        je   .end
        mov  ah, 0Eh        ; Numero de funcion para escribir en terminal 
        int  10h            ; Interrupcion para servicios de vídeo de bios
        inc  si
        jmp  .loop
    .end:
        ret