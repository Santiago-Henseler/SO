#ifndef MEMORY_H
#define MEMORY_H

// Headers extra
#include "stdio.h"
#include "stdbool.h"
#include "../memory/memBlock.h"

#define NULL 0

struct allocBlock {
    uint32 * addr;
    // Tamaño del bloque
    uint32 size;
    // Apunta al bloque anterior libre
    struct allocBlock * prev;
    // Apunta al bloque siguiente libre
    struct allocBlock * next;
}; 

// Devuelve un puntero al primer byte de un bloque de tamaño indicado
void * malloc(uint32 size);









#endif