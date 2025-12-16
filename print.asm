print:
    mov ax, cs              ; Guardo el addr base de este codigo (cs) en ds
    mov ds, ax              ; para actualizar el data segment a este scope
    mov  si, initmsg        
  loop: lodsb               ; Copia el primer byte de lo que esta en [si] a al e incrementa si en 1
        cmp al, 0
        je   end
        mov  ah, 0Eh        ; Numero de funcion para escribir en terminal 
        int  10h            ; Interrupcion para servicios de vídeo de bios
        jmp  loop
  end:  ret

initmsg db "Iniciando Sistema Operativo", 0Dh, 0Ah, 0 