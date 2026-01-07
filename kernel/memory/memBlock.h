#ifndef MEMBLOCK_H
#define MEMBLOCK_H

// Headers extra
#include "../lib/stdint.h"
#include "../lib/memory.h"
#include "../lib/stdbool.h"

#define BLOCK_SIZE 4096
#define BLOCKS  4    // 16 MB de memoria ( por ahora)

struct memBlock{
    uint32 * addr;
    // Apunta al bloque anterior libre
    struct memBlock * prev;
    // Apunta al bloque siguiente libre
    struct memBlock * next;
};

// Incia todos los bloques de memoria en una lista enlazada 
void initMemBlock(uint32 memSize);

// Devuelve un puntero al primer byte de memoria de un bloque
void * getMemBlock();

// Libera la memoria del puntero dado 
void freeMemBlock(uint8 * addr);

#endif