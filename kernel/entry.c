#include "drivers/vga/vga.h"
#include "lib/stdio.h"
#include "interrupts/idt.h"
#include "memory/memBlock.h"

#include "lib/memory.h"

void main(int16 memSize){
    clearVga();

    initInterrupts();
    printf("[Info] Se entro en modo protegido y se activaron las interrupciones \n");

    initMemBlock(0);

    struct allocBlock * a = malloc(sizeof(int));

    struct allocBlock * b = a -1;

    printf("%i - %i", sizeof(int), b->size);   

    for (;;);
}