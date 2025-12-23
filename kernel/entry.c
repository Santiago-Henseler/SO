#include "drivers/vga/vga.h"
#include "lib/stdio.h"
#include "interrupts/idt.h"


void main(){
    clearVga();
    initInterrupts();

        printf("a");

    asm volatile("int 0x0");

    printf("[Info] Se entro en modo protegido y se activaron las interrupciones \n");


    for (;;);
}