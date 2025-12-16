org 0x7c00              ; Dirección del PC donde salta la BIOS al terminar
bits 16
start:  jmp boot

boot:
        cli                 ; Bloqueo las interrupciones
        cld
        mov  si, initmsg    
loop:   lodsb               ; Copia el primer byte de lo que esta en [si] a al e incrementa si en 1
        cmp al, 0
        je   end
        mov  ah, 0Eh        ; Numero de funcion para escribir en terminal 
        int  10h            ; Interrupcion para servicios de vídeo de bios
        jmp  loop
end:    hlt

initmsg db "Iniciando Sistema Operativo"

times 510 - ($-$$) db 0

dw 0xAA55               ; Indica a la bios que es el boot