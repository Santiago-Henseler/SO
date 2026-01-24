#ifndef STRING_H
#define STRING_H

// Headers extra
#include "ascii.h"
#include "stdmem.h"
#include "stdint.h"

// Bases para num y hex to str
#define HEX_BASE 16
#define DEC_BASE 10

// Dado un string terminado en \0 devuelve su largo (sin contar el \0)
uint32 strLen(const char *str);

// Dado un int devuelve un string terminado en \0
char * intToStr(int num);

// Dado un int(en hexa) devuelve un string terminado en \0 e iniciado en 0x
char * hexToStr(int num);

// Dado un string lo invierte
void strReverse(char *str);

#endif