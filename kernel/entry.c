#include "drivers/vga/vga.h"
#include "lib/stdio.h"
#include "interrupts/idt.h"
#include "memory/memBlock.h"

void main(int16 memSize){
    clearVga();

    initInterrupts();
    initMemBlock(memSize);

    printf("[Info] Se entro en modo protegido y se activaron las interrupciones \n");
    printf("[Info] Se inicio la memoria en bloques, espacio disponible: %i(16 MB) \n", BLOCK_SIZE * BLOCKS);

    for (;;);
}