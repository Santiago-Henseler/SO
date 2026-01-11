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

char* numToStr(int num){
    
    char * str = (char *) malloc(sizeof(char) * 12); // Como maximo puedo representar 2**32-1 numeros (entran en 12 caracteres)

    int j = 0;

    if(num == 0){
        // TODO: sigue sin printear el 0
        str[j] = KEY_0;
    }

    while (num > 0){
        str[j] = (num % DEC_BASE) + KEY_0;
        num /= DEC_BASE;
        j++;
    }

    str[j] = '\0';
    strReverse(str);

    return str;
}

char * hexToStr(int num){
    char * str = (char *) malloc(sizeof(char) * 12);

    int j = 0;
    char letra[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

    if(num == 0){
        // TODO: sigue sin printear el 0
        str[j] = KEY_0;
    }

    while (num > 0){
        if(num % HEX_BASE >= 10){
            str[j] = letra[(num % HEX_BASE) % 10];
        }else{
            str[j] = (num % HEX_BASE) + '0';
        }
        num /= HEX_BASE;
        j++;
    }
    str[j++] = 'X';
    str[j++] = '0';
    str[j++] = '\0';
    strReverse(str);

    return str;
}

void strReverse(char *str){

    int len = strLen(str);

    for (int i = 0; i < len/2 ; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}
