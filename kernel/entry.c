#include "drivers/vga/vga.h"
#include "lib/stdio.h"

void main(){
    clearVga();

    printf("%s %s", "[Info] Se entro en modo protegido y control del kernel\n", "niiiii");

    printVga("65",RED);

    for (;;);
}