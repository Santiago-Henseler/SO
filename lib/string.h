#ifndef STRING_H
#define STRING_H

// Headers extra
#include <ascii.h>
#include <stdmem.h>
#include <stdint.h>
#include <stdbool.h>

// Dado un str terminado en \0 devuelve su largo (sin contar el \0)
int32 strLen(const char *str);

// Dado un str lo invierte
int strReverse(char *str);

// Copia el str de src a dst
int strCopy(char * src, char * dst);

// Devuelve true si ambos str son iguales
bool strCompare(const char *first, const char *second);

// Concatena src al final de dst
int strConcat(char * src, char ** dst);

// Devuelve true si str contiene el caracter entre comillas simples
bool strContains(char * str, char c);

#endif