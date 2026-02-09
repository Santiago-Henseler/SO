#ifndef FILESYSTEM_H
#define FILESYSTEM_H

// Headers extra
#include <floppyDisk/floppy.h>
#include <stdbool.h>
#include <stdmem.h>
#include <stdint.h>


// Bloque donde se encuentra el superBloque
#define SUPER_BLOCK_POS 50

#define FILESYSTEM_BITMAP_SIZE 352 // (FLOPPY_MAX_BLOCK - SUPER_BLOCK_POS - 6 / 8) - 1 (resto 6 y 1 para que sea multiplo de 8)

// Codigo para indicar que el fileSystem esta creado
#define FILESYSTEM_CODE 270425

typedef struct superBlock{
    uint32 code; 
    uint32 inodes; // Canitdad de inodes
    uint32 root;
    uint8 bitMap[FILESYSTEM_BITMAP_SIZE]; // 0 => bloque libre
} superBlock;

typedef enum fileType{
    DIR,
    EXEC,
    DATA
}fileType;

typedef struct inode{

    fileType type;
    uint16 size;

}inode;


// Tamaño maximo del nombre de un archivo
#define FILE_NAME_SIZE 128

// Inicializa el fileSystem en memoria
void initFileSystem();


uint32 getFreeBlock();


#endif