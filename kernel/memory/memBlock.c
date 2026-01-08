#include "memBlock.h"

#include "../lib/stdio.h"

extern uint8 kernelEnd;

struct memBlock * rootBlock = NULL;
struct memBlock * rootUsedBlock = NULL;

void initMemBlock(uint32 memSize){

    uint8 * kernelEndAddr = ((uint8 * )&kernelEnd);
    uint32  blockLen = (BLOCKS * sizeof(struct memBlock));
    uint8 * blockAddr = (kernelEndAddr + blockLen);

    struct memBlock * block = (struct memBlock *) kernelEndAddr;

    block[0].next = &block[1];
    block[0].addr = blockAddr;
    rootBlock = &block[0];

    for(int i = 1; i < BLOCKS-1; i++){ 
        block[i].prev = &block[i-1];
        block[i].addr = blockAddr+i*BLOCK_SIZE;
        block[i].next = &block[i+1];
    }

    block[BLOCKS-1].prev = &block[BLOCKS-2];
    block[BLOCKS-1].addr = blockAddr+(BLOCKS-1)*BLOCK_SIZE;
    block[BLOCKS-1].next = &rootBlock;
    rootBlock->prev = block;
}

void * getMemBlock(){

    if(!rootBlock)
        // TODO: No hay mas memoria disponible
        return NULL;

    struct memBlock * block = rootBlock;

    if(rootBlock->next == rootBlock){
        rootBlock->next = NULL;
        rootBlock->prev = NULL;
        rootBlock = NULL;
    }else{
        rootBlock->prev->next = rootBlock->next;
        rootBlock->next->prev = rootBlock->prev;
        rootBlock = rootBlock->next;
    }

    if(rootUsedBlock == NULL){
        rootUsedBlock = block;
        rootUsedBlock->next = NULL;
    }
    else
        rootUsedBlock->next = block;

    void * addr = block->addr;
    block->addr = NULL;

    return addr;
}

void freeMemBlock(uint8 * addr){

    if(!addr)
        return;

    if(rootUsedBlock == NULL)
        return; // No hay ningun bloque en uso
    
    rootUsedBlock->addr = addr;
    rootUsedBlock->next = !rootBlock ? rootBlock->next : NULL;
    rootUsedBlock->prev = rootBlock;

    rootBlock = rootUsedBlock; 
    rootUsedBlock = rootUsedBlock->next;
}