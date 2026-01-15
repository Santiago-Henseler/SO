#include "memory.h"

typedef struct allockBlock {
    void * addr;
    uint32 size;
    struct allockBlock * prev;
    struct allockBlock * next;
    bool used;
} __attribute__((aligned(16))) allockBlock;

allockBlock * rootAllocBlock = NULL;

allockBlock * newAllockBlock(){
    allockBlock* new = (allockBlock *)getMemBlock();

    if(new == NULL)
        return NULL;

    new->size = BLOCK_SIZE;
    new->addr = new + 1;
    new->next = NULL; new->prev = NULL;
    new->used = false;

    return new;
}

void splitAllocBlock(allockBlock * left){
    allockBlock * right = (allockBlock *)((uint8 * )left + left->size/2); 

    right->addr = right + 1;
    right->next = left->next;
    right->prev = left; 
    right->used = false;
    
    left->next = right;
    left->size /= 2;
    right->size = left->size;
}

void joinAllocBlock(allockBlock * left){
    allockBlock * right = left->next;

    left->next = right->next;
    left->size += right->size;
}

// Devuelve un puntero al bloque libre 
void * getAllocBlock(uint32 size){
    uint32 realSize = size + sizeof(allockBlock);

    allockBlock * candidate = NULL;
    allockBlock * act = rootAllocBlock;
    allockBlock * last = NULL;

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
        // si se recorrio todos y no entraba, pido otro bloque
        allockBlock * new = newAllockBlock();
        if(new == NULL)
            return NULL;
        new->prev = last;
        last->next = new;
        candidate = new;
    }
    
    while(candidate->size/2 >= realSize){
        // Del bloque mas chico que hay lo ajusto lo mejor posible al tamaño pedido
        splitAllocBlock(candidate);
    }

    candidate->used = true;
    return candidate->addr;
}

void memcopy(void * old, void * new, uint32 size){

    uint8 * newB = (uint8 *) new;
    uint8 * oldB = (uint8 *) old;

    for(int i = 0; i < size; i++)
        newB[i] = oldB[i]; 
}

void * malloc(uint32 size){

    if(size > BLOCK_SIZE){
        // TODO: Deberia poder reservar secciones de memoria mas grandes
        return NULL;
    }

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

void * realloc(void * ptr, uint32 size){
    if(ptr == NULL)
        return NULL;

    allockBlock * old = ((allockBlock *)ptr)-1;
    uint32 realSize = size + sizeof(allockBlock);

    if(old->size >= realSize)
        return ptr;


    void * new = malloc(size);

    memcopy(ptr, new, old->size);

    free(ptr);

    return new;
}

void free(void * ptr){
    if(ptr == NULL)
        return;

    allockBlock * free = ptr-1;
    free->used = false;

    // Vuelvo a unir los bloques que estan libres
    allockBlock * act = rootAllocBlock;
    while (act != NULL)
    {
        allockBlock * next = act->next;
        if(next == NULL)
            goto end;
        if(act->size == next->size && !act->used && !next->used)
            joinAllocBlock(act); 
        end:    
            act = next;
    }
    
    // TODO: si el bloque entero esta libre devolver memoria al sisop
}