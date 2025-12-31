#include "memBlock.h"

#include "../lib/stdio.h"

struct memBlock blocks[BLOCKS];

void initMemBlock(uint32 memSize){

    uint8 * blockDir = (uint8 * )0x0;

    blocks[0].addr = blockDir;
    blocks[0].next = &blocks[1];
    blocks[0].prev = &blocks[BLOCKS-1];

    for(int i = 1; i < BLOCKS-1; i++){

        uint8 * dir = blockDir+i*BLOCK_SIZE;

        blocks[i].addr = dir;
        blocks[i].prev = &blocks[i-1];
        blocks[i].next = &blocks[i+1];
        
    }

    blocks[BLOCKS-1].addr = blockDir+(BLOCKS-1)*BLOCK_SIZE;
    blocks[BLOCKS-1].next = 0;
    blocks[BLOCKS-1].prev = &blocks[BLOCKS-2];
}