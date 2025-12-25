#include "interrupts.h"

void interruptSoftware(InterruptRegisters * interruptRegs);
void interruptHardware(InterruptRegisters * interruptRegs);

void (* handlers[32])(InterruptRegisters * interruptRegs) = {
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptHardware, &interruptHardware,
    &interruptHardware, &interruptHardware, &interruptHardware,
    &interruptHardware, &interruptHardware, &interruptHardware,
    &interruptHardware, &interruptHardware, &interruptHardware,
    &interruptHardware, &interruptHardware
};

void interrupthandler(InterruptRegisters * interruptRegs){

    if(interruptRegs->interrupt > 32){
        printf("[Error]: interrupción no soportada\n");
        // TODO: ejecutar kenel panic
        return;
    }

    handlers[interruptRegs->interrupt](interruptRegs);
}

void interruptRegsDump(InterruptRegisters * interruptRegs){
    printf("####################################\n");
    printf("Interrupt: %i\n", interruptRegs->interrupt);
}	

void interruptSoftware(InterruptRegisters * interruptRegs){
    interruptRegsDump(interruptRegs);
}

void interruptHardware(InterruptRegisters * interruptRegs){

    interruptRegsDump(interruptRegs);

    // ACK de la interrupcion al PIC
    outB(PIC_PRIMARY_PORT, 0x20);
}