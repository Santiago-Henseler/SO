#include "memory.h"

struct allocBlock {
    void * addr;
    uint32 size;
    struct allocBlock * prev;
    struct allocBlock * next;
    bool used;
} __attribute__((aligned(16)));

struct allocBlock * rootAllocBlock = NULL;

struct allocBlock * newAllockBlock(){
    struct allocBlock* new = (struct allocBlock *)getMemBlock();
    new->size = BLOCK_SIZE;
    new->addr = new + 1;
    new->next = NULL; new->prev = NULL;
    new->used = false;

    return new;
}

void splitAllocBlock(struct allocBlock * left){
    struct allocBlock * right = (struct allocBlock *)((uint8 * )left + left->size/2); 

    right->addr = right + 1;
    right->next = left->next;
    right->prev = left; 
    right->used = false;
    
    left->next = right;
    left->size /= 2;
    right->size = left->size;
}

void joinAllocBlock(struct allocBlock * left){
    struct allocBlock * right = left->next;

    left->next = right->next;
    left->size += right->size;

}

// Devuelve un puntero al bloque libre 
void * getAllocBlock(uint32 size){

    uint32 realSize = size + sizeof(struct allocBlock);

    struct allocBlock * candidate = NULL;
    struct allocBlock * act = rootAllocBlock;
    struct allocBlock * last = NULL;

    while(act != NULL){
        if(act->size >= realSize){
            // De todos los bloques agarro el mas chiquito de todos
            if(candidate == NULL && !act->used)
                candidate = act;
            else if(candidate->size > act->size && !act->used)
                candidate = act;
        }
        last = act;
        act = act->next;
    }

    if(candidate == NULL){
        // si se recorrio todos y no entraba, pedir otro bloque
        struct allocBlock * new = newAllockBlock();
        new->prev = last;
        //new->next = rootAllocBlock;
        last->next = new;
        candidate = new;
    }
    
    while(candidate->size/2 >= realSize){
        splitAllocBlock(candidate);
    }

    candidate->used = true;
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

void * calloc(uint32 size){

    uint8 * addr = (uint8 *)malloc(size);

    for (int i = 0; i < size; i++){
        uint8 * cAddr = addr +i;
        *cAddr = 0;
    }
    return addr;
}

void free(void * addr){
    // TODO: hacer esto de manera mas eficiente es un asco
    struct allocBlock * act = rootAllocBlock;
    bool found = false;

    while(act != NULL && !found){
        if(act->addr == addr){
            found = true;
            act->used = false;
        }
        act = act->next;
    }

    act = rootAllocBlock;
    while (act != NULL)
    {
        struct allocBlock * next = act->next;
        if(next == NULL)
            goto end;
        if(act->size == next->size && !act->used && !next->used)
            joinAllocBlock(act);
        else 
        end:    act = act->next;
    }
    
    // TODO: si el bloque entero esta libre devolver memoria al sisop
}