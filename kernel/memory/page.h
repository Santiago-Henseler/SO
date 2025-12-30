#ifndef PAGE_H
#define PAGE_H

// Headers extra
#include "../lib/stdint.h"

// Cantidad de entradas en la page directory
#define PAGE_DIR_SIZE 1024

// Cantidad de entradas en la page table
#define PAGE_TABLE_SIZE 1024

// bits 31..12 de direccion de la page table entry 
// bit 7 para tamaño de pagina (0 = 4Kb)  
// bit 4 para no cachear la pagina
// bit 3 para habilitar el write-through
// bit 2 para control (user = 1)/(kernel = 0) 
// bit 1 para habilitar lectura y escritura
// bit 0 presente
int32 pageDirectory[PAGE_DIR_SIZE] __attribute__((aligned(4096)));

// bits 31..12 de direccion de una pagina
// bit 8 para indicar pagina global
// bit 6 para indicar si la pagina fue usada  
// bit 4 para no cachear la pagina
// bit 3 para habilitar el write-through
// bit 2 para control (user = 1)/(kernel = 0) 
// bit 1 para habilitar lectura y escritura
// bit 0 presente
typedef int32 pageTableEntry;


#endif