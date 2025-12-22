#include "drivers/vga/vga.h"
#include "lib/stdio.h"
#include "lib/string.h"

void main(){
    clearVga();

    //printf("%s  nnn %s", "[Info] Se entro en modo protegido y control del kernel\n", "niiiii");

    //printf("Largo total: %i", strLen("hello word"));

    char * s = "Hellooo word";

    strReverse(s);

    printf("%s", s);

    for (;;);
}