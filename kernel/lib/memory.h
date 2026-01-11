#ifndef MEMORY_H
#define MEMORY_H

// Headers extra
#include "stdio.h"
#include "stdbool.h"
#include "../memory/memBlock.h"

#define NULL 0

// Devuelve un puntero al primer byte de un bloque de tamaño indicado
void * malloc(uint32 size);

// Devuelve un puntero al primer byte de un bloque de tamaño indicado inicializado en 0
void * calloc(uint32 size);

// Libera la memoria indicada
void free(void *);

#endif