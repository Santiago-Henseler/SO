#ifndef STRING_H
#define STRING_H

// Headers extra
#include <ascii.h>
#include <stdmem.h>
#include <stdint.h>
#include <stdbool.h>

// Dado un string terminado en \0 devuelve su largo (sin contar el \0)
int32 strLen(const char *str);

// Dado un string lo invierte
int strReverse(char *str);

// Copia el string de src a dst
int strCopy(char * src, char * dst);

// Devuelve true si ambos str son iguales
bool strCompare(const char *first, const char *second);

#endif