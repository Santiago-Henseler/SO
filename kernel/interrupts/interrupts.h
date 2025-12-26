#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// Headers extra
#include "../drivers/keyboard/keyboard.h"
#include "../lib/stdint.h"
#include "../lib/stdio.h"
#include "pic.h"

typedef struct {
    uint32 ds;                                            // Data segment
    uint32 edi, esi, ebp, useless, ebx, edx, ecx, eax;    // Registros comunes
    uint32 interrupt;                                     // Coodigo de interrupcion 
    uint32 error;                                         // Codigo de error (si lo pushea la cpu)
    uint32 eip, cs, eflags, esp, ss;                      // Pusheado por la cpu en la interrupcion
} __attribute__((packed)) InterruptRegisters;

// Encargado de manejar todas las interrupciones
void interrupthandler(InterruptRegisters * interrupt);

#endif