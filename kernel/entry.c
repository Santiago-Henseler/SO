#include "drivers/vga/vga.h"

void main(){

    char s[] = "[Info] Se entro en modo protegido y control del kernel\n";

    clearVga();

    printVga(WHITE, "Hola\n");
printVga(WHITE, "Mundo\n");
printVga(WHITE, "Kernel OK\n");


    for (;;);
}