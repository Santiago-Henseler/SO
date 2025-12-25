#include "stdio.h"

void printf(char* str, ...){
    // TODO: ver de optimizar cuando tenga memoria dinamica
    va_list args;
    va_start(args, str);

    char * txt = str;

    while (*txt)
    {
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
                    int num = va_arg(args, int);

                    // TODO: cambiar a numToStr cuando maneje memoria dinamica
                    // TODO: soportar el numero 0
                    char p[12];
                    int j = 0;
                
                    while (num){
                        p[j] = num%10 + '0';
                        num /= 10;
                        j++;
                    }

                    p[j] ='\0';

                    strReverse((char *)&p);
                    printVga(p, WHITE);

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

