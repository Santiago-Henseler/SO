#include "interrupts.h"
#include "../lib/stdio.h"

void interrupthandler(InterruptRegisters * interrupt){
    printf("Interrupcion: %i", interrupt->interrupt);
}