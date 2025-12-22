#include "stdio.h"

void printf(const char* str, ...){
    
    va_list args;
    va_start(args, str);

    char * format;
    int i = 0;

    while (*str)
    {
        if(*str == '%'){
            str++;
            switch (*str){
                case 's':
                    char * s = va_arg(args, char *);
                    while (*s){
                        format[i] = *s;
                        s++; i++;
                    }
                    break;
                case 'i':
                    int i = va_arg(args, int);

                    
                     
                    break;
                default:
                    break;
            }
        }else{
            format[i] = *str;
            i++;
        }
        str++;
    }
    
    va_end(args);

    format[i++] = '\0';

    printVga(format, WHITE);

    return;
}
