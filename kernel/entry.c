#include <vga.h>
#include <stdio.h>
#include <idt.h>
#include <block.h>
#include <page.h>

void main(int16 memSize){
    clearVga();

    initInterrupts();
    initMemBlock(memSize);
    initPageTable();

    printf("[Info] Se entro en modo protegido y se activaron las interrupciones \n");
    printf("[Info] Se inicio la memoria en bloques, espacio disponible: %i(16 MB) \n", PAGE_SIZE * BLOCKS);
    printf("[info] Se inicio la memoria paginada\n");

    for (;;);
}