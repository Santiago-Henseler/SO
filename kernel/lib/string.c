#include "string.h"

uint32 strLen(const char *str){
    int len = 0;    
    while (*str)
    {
        len++;
        str++;
    }
    return len;
}


void strReverse(char *str){

    int len = strLen(str);

    for (int i = 0; i < len/2 ; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}