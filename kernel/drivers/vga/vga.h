#ifndef VGA_H
#define VGA_H

// Headers extra 
#include "../io.h"
#include "../../lib/ascii.h"

// Tamaño de la pantalla 
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Vga ports para mover el cursor 
#define COMMAND_PORT_VGA 0x3D4
#define DATA_PORT_VGA 0x3D5

// Colors definition 
#define BLACK 0
#define BLUE  1
#define GREEN 2
#define RED   4
#define WHITE 7

// Escribo el str* sobre la memoria mapeada de la vga respetando el cursor
void printVga(const char* str, int color);

// Limpio toda la memoria mapeada de la vga 
void clearVga(void);

#endif