#include "drivers/vga/vga.h"
#include "lib/stdio.h"

void main(){
    clearVga();

    //printf("%s  nnn %s", "[Info] Se entro en modo protegido y control del kernel\n", "niiiii");

      char caracter_ascii = (char)(5 + '0');

    printVga( caracter_ascii, RED);

    for (;;);
}