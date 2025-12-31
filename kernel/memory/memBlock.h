#ifndef MEMBLOCK_H
#define MEMBLOCK_H

// Headers extra
#include "../lib/stdint.h"

#define BLOCK_SIZE 4096
#define BLOCKS  4096    // 16 MB de memoria ( por ahora)

struct memBlock{
    uint32 * addr;
    // Apunta al bloque anterior libre
    struct memBlock * prev;
    // Apunta al bloque siguiente libre
    struct memBlock * next;
};


void initMemBlock(uint32 memSize);

#endif