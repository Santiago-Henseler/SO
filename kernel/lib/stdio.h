#ifndef STDIO_H
#define STDIO_H

// Headers extra //
#include "../drivers/vga/vga.h"
#include "string.h"
#include "stdarg.h"

// Muestra en pantalla agregando el formato indicado 
// Soportado:  %s => char * ;  %i => int  ;  %c => char         
void printf(const char* str, ...);

#endif