#ifndef STRING_H
#define STRING_H

// Headers extra
#include "ascii.h"
#include "stdmem.h"
#include "stdint.h"

// Dado un string terminado en \0 devuelve su largo (sin contar el \0)
uint32 strLen(const char *str);

// Dado un string lo invierte
void strReverse(char *str);

#endif