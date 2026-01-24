#ifndef MEMBLOCK_H
#define MEMBLOCK_H

// Headers extra
#include "../lib/stdint.h"
#include "../lib/stdmem.h"
#include "../lib/stdbool.h"

#define BLOCK_SIZE 4096
#define BLOCKS  4096    // 16 MB de memoria ( por ahora)

// Incia todos los bloques de memoria en una lista 
void initMemBlock(uint32 memSize);

// Devuelve un puntero al primer byte de memoria de un bloque
void * getMemBlock();

// Libera la memoria del puntero dado 
void freeMemBlock(void * addr);

#endif