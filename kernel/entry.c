#include "drivers/vga.h"

void main(){

    char s[] = "[Info] Se entro en modo protegido y control del kernel\n";

    clearVga();

    for(int i = 0; i< 12; i++){
            printVga(GREEN, s);   
            printVga(BLUE, s); 
    }

    printVga(BLUE, s);
    printVga(BLUE, s);
    printVga(BLUE, s);

    for (;;);
}