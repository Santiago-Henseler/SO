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

void numToStr(int num, char *str){
    int j = 0;

    while (num > 0){
        str[j] = num%10 + '0';
        num /= 10;
        j++;
    }

    str[j] = '\0';
    strReverse(str);
}

void hexToStr(int num, char *str){
    int j = 0;
    char l[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

    while (num > 0){
        if(num%16 >= 10){
            str[j] = l[(num%16)%10];
        }else{
            str[j] = num%16 + '0';
        }
        num /= 16;
        j++;
    }
    str[j++] = 'X';
    str[j++] = '0';
    str[j++] = '\0';
    strReverse(str);

}

void strReverse(char *str){

    int len = strLen(str);

    for (int i = 0; i < len/2 ; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}
