#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// Headers extra
#include "../lib/stdint.h"
#include "../lib/stdio.h"
#include "pic.h"

typedef struct {
    uint32 ds;                                            // data segment
    uint32 edi, esi, ebp, useless, ebx, edx, ecx, eax;    // pusha
    uint32 interrupt, error;                              // Coodigo de interrupcion y Codigo de error (si lo pushea la cpu)
    uint32 eip, cs, eflags, esp, ss;                      // Pusheado por la cpu en la interrupcion
} __attribute__((packed)) InterruptRegisters;


// Encargado de manejar todas las interrupciones
void interrupthandler(InterruptRegisters * interrupt);

#endif