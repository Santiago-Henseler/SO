#include "stdio.h"

void printf(const char* str, ...){
    
    va_list args;
    va_start(args, str);

    char * txt = str;
    char * format;
    int i = 0;

    while (*txt)
    {
        if(*txt == '%'){
            txt++;
            switch (*txt){
                case 's':
                    char * s = va_arg(args, char *);
                    while (*s){
                        format[i] = *s;
                        s++; i++;
                    }
                    break;
                case 'c':
                    char * c = va_arg(args, char *);
                    format[i] = c;
                    i++;
                    break;
                case 'i':
                    int num = va_arg(args, int);

                    // TODO: cambiar a numToStr cuando maneje memoria dinamica
                    char *p;
                    int j = 0;

                    while (num){
                        p[j] = num%10 + '0';
                        num /= 10;
                        j++;
                    }

                    for(j--; j>=0; j--){
                        format[i] = p[j];
                        i++;
                    }
                    break;
                default:
                    break;
            }
        }else{
            format[i] = *txt;
            i++;
        }
        txt++;
    }
    
    va_end(args);

    format[i++] = '\0';

    printVga(format, WHITE);

    return;
}
