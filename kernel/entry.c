#include "drivers/vga/vga.h"
#include "lib/stdio.h"
#include "lib/string.h"

void main(){
    clearVga();

    printf("sdsdsd %s %i %c \n",  "AAA", 30, 'a');

    printf("Largo total de %s: %i\n", "hello word" ,strLen("hello word"));

    char * s = "Hellooo word";

    strReverse(s);

    printf("%s", s);

    for (;;);
}