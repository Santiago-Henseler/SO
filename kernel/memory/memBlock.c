#include "memBlock.h"

extern uint8 kernelEnd;

struct memBlock * rootBlock = NULL;

void initMemBlock(uint32 memSize){

    uint8 * kernelEndAddr = ((uint8 * )&kernelEnd);
    uint32  blockLen = (BLOCKS * sizeof(struct memBlock));
    uint8 * blockAddr = (kernelEndAddr + blockLen);

    struct memBlock * block = (struct memBlock *) kernelEndAddr;

    block->next = ++block;
    block->addr = blockAddr;
    rootBlock = block;

    for(int i = 1; i < BLOCKS-1; i++){ 
        block->prev = --block; block++;
        block->addr = blockAddr+i*BLOCK_SIZE;
        block->next = ++block;
    }

    block->prev = --block; block++;
    block->addr = blockAddr+(BLOCKS-1)*BLOCK_SIZE;
    block->next = rootBlock;
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

    void * addr = block->addr;
    block->addr = NULL;

    return addr;
}

void freeMemBlock(uint8 * addr){

    if(!addr)
        return;
    
    uint8 * kernelEndAddr = ((uint8 * )&kernelEnd);
    struct memBlock * block = (struct memBlock *) kernelEndAddr;

    bool found = false; int i = 0;
    while(!found && i < BLOCKS-1){
        if(block->addr == NULL){
            block->next = rootBlock->next;
            block->prev = rootBlock;
            block->addr = addr;
            rootBlock->next = block;
        }
        else{
            i++;
            block++;
        }
    }

    if(!found)
        return; // puede llegar a pasar esto (?

}