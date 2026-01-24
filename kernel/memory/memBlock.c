#include "memBlock.h"

typedef struct memBlock{
    void * addr;
    struct memBlock * next;
} memBlock;

extern uint8 kernelEnd;

memBlock * rootBlock = NULL;
memBlock * rootUsedBlock = NULL;

void initMemBlock(uint32 memSize){

    uint8 * kernelEndAddr = ((uint8 * )&kernelEnd);
    uint32  blockLen = (BLOCKS * sizeof(memBlock));
    uint8 * blockAddr = ALIGN(kernelEndAddr + blockLen, 16);

    memBlock * block = (memBlock *) kernelEndAddr;

    block[0].next = &block[1];
    block[0].addr = blockAddr;

    for(int i = 1; i < BLOCKS-1; i++){ 
        block[i].addr = blockAddr + i*(BLOCK_SIZE);
        block[i].next = &block[i+1];
    }

    block[BLOCKS-1].addr = blockAddr+(BLOCKS-1)*BLOCK_SIZE;
    block[BLOCKS-1].next = NULL;

    rootBlock = &block[0];
}

void * getMemBlock(){

    if(!rootBlock) // TODO: No hay mas memoria disponible
        return NULL;

    memBlock * block = rootBlock;

    rootBlock = rootBlock->next;
    block->next = rootUsedBlock; 
    rootUsedBlock = block;

    return block->addr;
}

void freeMemBlock(void * addr){

    if(!addr)
        return;

    if(!rootUsedBlock)
        return; // No hay ningun bloque en uso
    
    memBlock * prev = NULL;
    memBlock * act = rootUsedBlock;
    bool found = false;
    
    while(act != NULL && !found){
        if(act->addr == addr){
            if(prev != NULL)
                prev->next = act->next;
            else
                rootUsedBlock = act->next;
            act->next = rootBlock;
            rootBlock = act;
            found = true;
        }   
        prev = act;
        act = act->next;
    }
}