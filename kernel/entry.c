#include <vga.h>
#include <stdio.h>
#include <idt.h>
#include <block.h>
#include <page.h>
#include <syscall.h>
#include <floppy.h>

extern uint8 kernelEnd;
extern uint8 kernelStart;

void main(uint32 memRamSize){
    clearVga();

    initInterrupts();
    
    uint32 kernelSize = (uint32)&kernelEnd - (uint32)&kernelStart;
    initMemBlock(memRamSize - kernelSize);
    initPageTable(memRamSize - kernelSize);

    initFloppyDisk();

    printf("[Info] Se entro en modo protegido y se activaron las interrupciones \n");
    printf("[Info] Se inicio la memoria en bloques, espacio disponible: %i \n", memRamSize - kernelSize);
    printf("[info] Se inicio la memoria paginada\n");  
    printf("[info] Se inicio el driver del floppy disk\n");  


    uint8 buff[FLOPPY_BLOCK];

    for(int i = 0; i < FLOPPY_BLOCK; i++)
        buff[i] = 9;

    int a = writeFloppyDisk(15, buff);  

    printf("%i \n", a);

    uint8 buff2[FLOPPY_BLOCK];

    int b = readFloppyDisk(15, buff);  

    printf("%i\n", b);

    for(int i = 0; i < FLOPPY_BLOCK; i++)
        printf("%i", buff2[i]);

    for (;;);
}