#ifndef BLOCK_H
#define BLOCK_H

// Headers extra
#include <stdint.h>
#include <stdmem.h>
#include <stdbool.h>
#include <page.h>

typedef struct memBlock{
    void * addr;
    struct memBlock * next;
} memBlock;

// Incia todos los bloques de memoria en una lista 
void initMemBlock(uint32 memSize);

// Devuelve un puntero al primer byte de memoria fisica de un bloque
void * getBlock();

// Libera la memoria del puntero dado 
void freeBlock(void * addr);

#endif