#include "drivers/vga/vga.h"

void main(){
    clearVga();

    printVga(WHITE, "[Info] Se entro en modo protegido y control del kernel\n");  


    for (;;);
}