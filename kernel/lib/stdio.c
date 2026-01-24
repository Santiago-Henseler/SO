#include "stdio.h"

void appendStr(char * src, char ** dst, uint32 memLen, int i){
    if(strLen(*dst)+strLen(src)+1 > memLen){
        *dst = (char *) realloc(*dst, strLen(*dst)+strLen(src)+1);
    }
    memCopy(src, &(*dst)[i], strLen(src)+1);
}

void printf(char* str, ...){
    // TODO: reemplazar printVga por syscall write (cuando exista)
    va_list args;
    va_start(args, str);

    uint32 memLen = strLen(str);
    char * txt = (char * )malloc(memLen+1);    

    if(txt == NULL)
        return;

    int i = 0;
    txt[i] = '\0';

    while (*str){
        if(*str == '%'){
            str++;
            switch (*str){
                case 's':
                    char * s = va_arg(args, char *);
                    appendStr(s, &txt, memLen, i);
                    i += strLen(s); memLen += strLen(s);
                    break;
                case 'c':
                    char c = va_arg(args, int);
                    char format[2] = {c, '\0'};
                    appendStr(format, &txt, memLen, i);
                    i++; memLen++;
                    break;
                case 'i':
                    int num = va_arg(args, int);
                    char * p = intToStr(num);
                    appendStr(p, &txt, memLen, i);
                    i += strLen(p); memLen += strLen(p);
                    free(p);
                    break;
                case 'x':
                    int hex =  va_arg(args, int);
                    char * hp = hexToStr(hex);
                    appendStr(hp, &txt, memLen, i);
                    i += strLen(hp); memLen += strLen(hp);
                    free(hp);
                    break;
                case 'b':
                    int boolean =  va_arg(args, int);
                    char * txtBool = boolean ? "True\0" : "False\0"; 
                    appendStr(txtBool, &txt, memLen, i);
                    i += strLen(txtBool); memLen += strLen(txtBool);
                    break;
                default:
                    break;
            }
        }else{
            char format[2] = {*str, '\0'};
            appendStr(format, &txt, memLen, i);
            i++; memLen++;
        }
        str++;
    }

    printVga(txt, WHITE);
    free(txt);
    
    va_end(args);
}

void putChar(char c){
    printf("%c", c);
}

void putInt(int i){
    printf("%i", i);
}