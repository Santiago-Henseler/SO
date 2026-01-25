#include "block.h"

typedef struct memBlock{
    void * addr;
    struct memBlock * next;
} memBlock;

//extern uint8 kernelEnd; TODO: deberia utilizar esto
#define kernelEnd 0x100000

memBlock * rootBlock = NULL;
memBlock * rootUsedBlock = NULL;

// Utilizo la primera seccion de memoria para guardar los structs
// organizados en 2 listas discriminando libres y usados
// para cuando se haga free del bloque chequear que el puntero dado sea correcto 
void initMemBlock(uint32 memSize){

    uint8 * kernelEndAddr = ((uint8 * )kernelEnd);
    uint32  blockLen = (BLOCKS * sizeof(memBlock));
    uint8 * blockAddr = ALIGN(kernelEndAddr + blockLen, 16);

    memBlock * block = (memBlock *) kernelEndAddr;

    block[0].next = &block[1];
    block[0].addr = blockAddr;

    for(int i = 1; i < BLOCKS-1; i++){ 
        block[i].addr = blockAddr + i*(BLOCK_SIZE);
        block[i].next = &block[i+1];
        memSet(block[i].addr, 1, BLOCK_SIZE);
    }

    block[BLOCKS-1].addr = blockAddr+(BLOCKS-1)*BLOCK_SIZE;
    block[BLOCKS-1].next = NULL;

    rootBlock = &block[0];
}

void * getBlock(){

    if(!rootBlock) // TODO: No hay mas memoria disponible
        return NULL;

    memBlock * block = rootBlock;

    rootBlock = rootBlock->next;
    block->next = rootUsedBlock; 
    rootUsedBlock = block;

    return block->addr;
}

void freeBlock(void * addr){

    if(!addr)
        return;

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