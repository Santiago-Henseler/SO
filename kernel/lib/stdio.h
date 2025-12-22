#ifndef STDIO_H
#define STDIO_H

// Headers extra //
#include "../drivers/vga/vga.h"
#include "stdarg.h"

// Muestra en pantalla agregando el formato indicado 
// Soportado:  %s => char * ;  %i => int             
void printf(const char* str, ...);

#endif