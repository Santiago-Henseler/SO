#ifndef STRING_H
#define STRING_H

// Dado un string terminado en \0 devuelve su largo (sin contar el \0)
int strLen(const char *str);

// Dado un int devuelve un string terminado en \0
// TODO: que devuelva char *  y que pueda printear el 0
void numToStr(int num, char *str);

// Dado un int(en hexa) devuelve un string terminado en \0  e iniciado en 0x
void hexToStr(int num, char *str);

// Dado un string lo invierte
void strReverse(char *str);

#endif