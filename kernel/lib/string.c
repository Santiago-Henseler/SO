#include "string.h"

#include "stdio.h"

int strLen(const char *str){
    int len = 0;    
    while (*str)
    {
        len++;
        str++;
    }
    return len;
}

char * numToStr(int num){
//   TODO
//    int i = 0;
//    char * str = malloc();
//
//    while (num){
//        str[i] = num%10 + '0';
//        num /= 10;
//        i++;
//    }
//
//    return strReverse(str);
}

void strReverse(char *str){

    int len = strLen(str);

    for (int i = 0; i < len/2 ; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}
