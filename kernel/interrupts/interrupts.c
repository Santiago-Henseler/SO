#include "interrupts.h"

char * interruptName[32] = {
    "Se intento dividir por 0", "Debug int", "NMI int",
    "Breackpoint int", "Ocurrio un overflow", "Operacion se fue de rango",
    "Codigo de operación invalido", "PC sin coprocesador", "Doble fallo",
    "", "TSS invalido", "Segmento no presente",
    "Fallo de segmento del stack", "Referencia a memoria protegida", "Fallo de pagina",
    "", "Error en la unidad de punto flotante", "",
    "", "", "", "", "","","","","","","","","",""
};

void interruptSoftware(InterruptRegisters * interruptRegs){
    printf("####################################\n");
    printf("Interrupt: %i Error: %x \n", interruptRegs->interrupt, interruptRegs->error);
    printf("%s \n", interruptName[interruptRegs->interrupt]);
    printf("eip => %x  esp => %x  flags => %x \n", interruptRegs->eip, interruptRegs->esp, interruptRegs->eflags);
    printf("####################################\n");
    for(;;); // TODO: kernel panic
}

void interruptHardware(InterruptRegisters * interruptRegs){

    printf("interrupt %i \n", interruptRegs->interrupt);

    // ACK de la interrupcion al PIC
    ackPic(interruptRegs->interrupt-32);
}

void keyboardInterrupt(InterruptRegisters *interruptRegs){
    
    char key = getKeyInput();
    // TODO: en vez de printear enviar al proceso que esta corriendo
    putChar(key);

    // ACK de la interrupcion al PIC
    ackPic(interruptRegs->interrupt-32);
}

void clockInterrupt(InterruptRegisters * interruptRegs){
    // TODO: cambiar de contexto cuando haya multitask
    
    // ACK de la interrupcion al PIC
    ackPic(interruptRegs->interrupt-32);
}

// Hardware interrupt handlers
void (* hardwareHandlers[PICS])(InterruptRegisters * interruptRegs) = {
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
        for(;;);
    }

    if(interruptRegs->interrupt > 31){
        hardwareHandlers[interruptRegs->interrupt-32](interruptRegs);
    }else{
        interruptSoftware(interruptRegs);
    }
}
