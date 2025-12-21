#include "stdio.h"

void printf(const char* str, ...){
    
    va_list args;

    va_start(args, str);

    while (*str)
    {
        if(*str == '%'){
            str++;
            switch (*str){
                case 's':
                    char * s = va_arg(args, char *);
                    printVga(s, WHITE); // TODO: debo apendear el str al texto
                    break;
                case 'i':
                    int i = va_arg(args, int);
                    printVga(i, RED); // TODO: debo poder printear enteros 
                    break;
                default:
                    break;
            }
        }
        str++;
    }
    
    va_end(args);

    return;
}
