#include "drivers/vga/vga.h"
#include "lib/stdio.h"
#include "interrupts/idt.h"
#include "memory/memBlock.h"

#include "lib/memory.h"

struct allocBlock {
    void * addr;
    uint32 size;
    struct allocBlock * prev;
    struct allocBlock * next;
    bool used;
} __attribute__((aligned(16)));

void main(int16 memSize){
    clearVga();

    initInterrupts();
    printf("[Info] Se entro en modo protegido y se activaron las interrupciones \n");

    initMemBlock(0);
    printf("[Info] Se inicio la memoria en bloques (16 MB) \n");

    for (;;);
}