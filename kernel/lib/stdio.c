#include "stdio.h"

void printf(char* str, ...){
    // TODO: ver de optimizar cuando tenga memoria dinamica
    // TODO: reemplazar printVga por syscall write (cuando exista)
    va_list args;
    va_start(args, str);

    char * txt = str;

    while (*txt){
        if(*txt == '%'){
            txt++;
            switch (*txt){
                case 's':
                    char * s = va_arg(args, char *);
                    printVga(s, WHITE);
                    break;
                case 'c':
                    char c = va_arg(args, int);
                    char format[2] = {c, '\0'};
                    printVga(format, WHITE);
                    break;
                case 'i':
                    int num = va_arg(args, int); // Realmente es unsigned int lo que representa
                    char * p = numToStr(num);
                    printVga(p, WHITE);
                    free(p);
                    break;
                case 'x':
                    int hex =  va_arg(args, int);
                    char * hp = hexToStr(hex);
                    printVga(hp, WHITE);
                    free(hp);
                    break;
                case 'b':
                    int boolean =  va_arg(args, int);
                    if(boolean)
                        printVga("True", WHITE);
                    else
                        printVga("False", WHITE);
                    break;
                default:
                    break;
            }
        }else{
            char format[2] = {*txt, '\0'};
            printVga(format, WHITE);
        }
        txt++;
    }
    
    va_end(args);
    return;
}

void putChar(char c){
    printf("%c", c);
}

void putInt(int i){
    printf("%i", i);
}

