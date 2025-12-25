#ifndef STDIO_H
#define STDIO_H

// Headers extra //
#include "../drivers/vga/vga.h"
#include "string.h"
#include "stdarg.h"

// Muestra en pantalla agregando el formato indicado 
// Soportado:  %s => char * ;  %i => int  ;  %c => char
//             %x => hexa       
void printf(char* str, ...);

// Wraper a printf para escribir un solo caracter
void putChar(char c);

// Wraper a printf para escribir un entero
void putInt(int i);

#endif