#ifndef MEMBLOCK_H
#define MEMBLOCK_H

// Headers extra
#include "../lib/stdint.h"

#define BLOCK_SIZE 4096

struct memBlock{
    char * addr;
    struct memBlock * prev;
    struct memBlock * next;
};


void initMemBlock(uint32 memSize);









#endif