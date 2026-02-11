#include "string.h"

int32 strLen(const char *str){
    
    if(str == NULL)
        return -1;

    int len = 0;    
    while (*str){
        len++;
        str++;
    }
    return len;
}

int strReverse(char *str){

    if(str == NULL)
        return -1;

    int len = strLen(str);

    for (int i = 0; i < len/2 ; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

int strCopy(char * src, char * dst){   

    if(src == NULL || dst == NULL)
        return -1;

    memCopy(src, dst, strLen(src));

    return 0;
}

bool strCompare(const char *first, const char *second){
    while (*first && *second) {
        if (*first != *second)
            return false;
        first++;
        second++;
    }
    return *first == *second;
}