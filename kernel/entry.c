#include "drivers/vga/vga.h"

void main(){

    clearVga();

    char s[] = "[Info] Se entro en modo protegido y control del kernel\n";

    printVga(WHITE, s);

    for (;;);
}