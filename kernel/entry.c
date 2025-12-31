#include "drivers/vga/vga.h"
#include "lib/stdio.h"
#include "interrupts/idt.h"
#include "memory/memBlock.h"


struct a{
    int b;
    uint32 c;
};

void main(int16 memSize){
    clearVga();

    initInterrupts();
    printf("[Info] Se entro en modo protegido y se activaron las interrupciones \n");

    initMemBlock(0);

    for (;;);
}