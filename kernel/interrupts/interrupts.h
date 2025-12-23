#ifndef INTERRUPTS_H
#define INTERRUPTS_H

typedef struct {
    int ds;                                            // data segment
    int edi, esi, ebp, useless, ebx, edx, ecx, eax;    // pusha
    int interrupt;                                     // Coodigo de interrupcion              
    int error;                                         // Codigo de error (si lo pushea la cpu)
    int eip, cs, eflags, esp, ss;                      // Pusheado por la cpu en la interrupcion
} __attribute__((packed)) InterruptRegisters;


// Encargado de manejar todas las interrupciones
void interrupthandler(InterruptRegisters * interrupt);

#endif