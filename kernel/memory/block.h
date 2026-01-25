#ifndef BLOCK_H
#define BLOCK_H

// Headers extra
#include <stdint.h>
#include <stdmem.h>
#include <stdbool.h>

#define BLOCK_SIZE 4096
#define BLOCKS  4096    // 16 MB de memoria ( por ahora)

// Incia todos los bloques de memoria en una lista 
void initMemBlock(uint32 memSize);

// Devuelve un puntero al primer byte de memoria de un bloque
void * getBlock();

// Libera la memoria del puntero dado 
void freeBlock(void * addr);

#endif