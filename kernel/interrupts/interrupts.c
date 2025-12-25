#include "interrupts.h"
#include "../lib/stdio.h"

void divZeroInterrupt(InterruptRegisters * interruptRegs);
void interruptRegsDump(InterruptRegisters * interruptRegs);

void (* handlers[32])(InterruptRegisters * interruptRegs) = {
    &divZeroInterrupt, &interruptRegsDump, &interruptRegsDump,
    &interruptRegsDump, &interruptRegsDump, &interruptRegsDump,
    &interruptRegsDump, &interruptRegsDump, &interruptRegsDump,
    &interruptRegsDump, &interruptRegsDump, &interruptRegsDump,
    &interruptRegsDump, &interruptRegsDump, &interruptRegsDump,
    &interruptRegsDump, &interruptRegsDump, &interruptRegsDump,
    &interruptRegsDump, &interruptRegsDump, &interruptRegsDump,
    &interruptRegsDump, &interruptRegsDump, &interruptRegsDump,
    &interruptRegsDump, &interruptRegsDump, &interruptRegsDump,
    &interruptRegsDump, &interruptRegsDump, &interruptRegsDump,
    &interruptRegsDump, &interruptRegsDump
};

void interrupthandler(InterruptRegisters * interruptRegs){

    if(interruptRegs->interrupt > 32){
        printf("[Error]: interrupción no soportada\n");
        // TODO: ejecutar kenel panic
        return;
    }

    handlers[interruptRegs->interrupt](interruptRegs);
}

void divZeroInterrupt(InterruptRegisters * interruptRegs){
    printf("[Error]: Se trato de dividir por 0\n");
}

void interruptRegsDump(InterruptRegisters * interruptRegs){
    printf("####################################\n");
    printf("Interrupt %i", interruptRegs->interrupt);
}	