#include "memory.h"

// TODO: lista de bloques libres tambien para el free
// TODO: implementar free, calloc 
struct allocBlock * rootAllocBlock = NULL;

struct allocBlock * newAllockBlock(){
    struct allocBlock* new = (struct allocBlock *)getMemBlock();
    printf("new block in %x\n", new);
    new->size = BLOCK_SIZE - sizeof(struct allocBlock);
    new->addr = new + 1;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

void splitAllocBlock(struct allocBlock * left){
    struct allocBlock * right = ((uint8 * )left->addr) + left->size/2; 

    right->addr = right + 1;
    right->next = left->next;
    right->prev = left; 

    left->next = right;
    left->size /= 2;
    right->size = left->size;
}

// Devuelve un puntero al bloque libre 
void * getAllocBlock(uint32 size){

    uint32 realSize = size + sizeof(struct allocBlock);

    struct allocBlock * candidate = NULL;

    struct allocBlock * act = rootAllocBlock;// TODO: chequear aca el act != NULL
    while(act != NULL){
        if(act->size >= realSize){
            // De todos los bloques agarro el mas chiquito de todos
            if(act->next == NULL)
                candidate = act;
            else if(candidate->size > act->size)
                candidate = act;
        }
        act = act->next;
    }

    if(candidate == NULL){
        // si se recorrio todos y no entraba, pedir otro bloque
        struct allocBlock * new = newAllockBlock();
        new->prev = act;
        act->next = new;
    }
    
    while(candidate->size/2 > realSize){
        splitAllocBlock(candidate);
    }

    // TODO: no marco como libre el bloque 

    return candidate->addr;
}

void * malloc(uint32 size){

    if(size > BLOCK_SIZE){
        // TODO: Deberia poder reservar secciones de memoria mas grandes
        return NULL;
    }

    if(!rootAllocBlock)
        rootAllocBlock = newAllockBlock();

    return getAllocBlock(size);
}