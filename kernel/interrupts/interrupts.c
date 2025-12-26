#include "interrupts.h"

void interruptRegsDump(InterruptRegisters * interruptRegs){
    printf("####################################\n");
    printf("Interrupt: %i Error: %x \n", interruptRegs->interrupt, interruptRegs->error);

    printf("eip => %x  esp => %x  flags => %x \n", interruptRegs->eip, interruptRegs->esp, interruptRegs->eflags);
}	

void interruptSoftware(InterruptRegisters * interruptRegs){
    interruptRegsDump(interruptRegs);
    for(;;);
}

void interruptHardware(InterruptRegisters * interruptRegs){


    // ACK de la interrupcion al PIC
    outB(PIC_PRIMARY_PORT, 0x20);
}

void keyboardInterrupt(InterruptRegisters *regs){
    
    char key = getKeyInput();

    printf("Key scancode: %c\n", key);

    // ACK de la interrupcion al PIC
    ackPic(1);
}

void clockInterrupt(InterruptRegisters * interrruptRegs){
    // TODO: cambiar de contexto cuando haya multitask
    // ACK de la interrupcion al PIC
    ackPic(0);
}

void (* handlers[48])(InterruptRegisters * interruptRegs) = {
    // Software interrupt handler
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware, &interruptSoftware,
    &interruptSoftware, &interruptSoftware,
    // Hardware interrupt handler
    &clockInterrupt, &keyboardInterrupt, &interruptHardware,
    &interruptHardware, &interruptHardware, &interruptHardware,
    &interruptHardware, &interruptHardware, &interruptHardware,
    &interruptHardware, &interruptHardware, &interruptHardware,
    &interruptHardware, &interruptHardware, &interruptHardware,
    &interruptHardware
};

void interrupthandler(InterruptRegisters * interruptRegs){

    if(interruptRegs->interrupt > 47){
        printf("[Error]: interrupción no soportada\n");
        // TODO: ejecutar kenel panic
        return;
    }

    handlers[interruptRegs->interrupt](interruptRegs);
}
