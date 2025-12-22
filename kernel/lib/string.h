#ifndef STRING_H
#define STRING_H

// Dado un string terminado en \0 devuelve su largo (sin contar el \0)
int strLen(const char *str);

// Dado un int devuelve un string terminado en \0
// TODO
char * numToStr(int num);

// Dado un string lo invierte
void strReverse(char *str);

#endif