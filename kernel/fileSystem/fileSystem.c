#include "fileSystem.h"

static superBlock sb;
superBlock *sBlock = &sb;

void initFileSystem(){
    uint8 buffer[FLOPPY_BLOCK_SIZE];
    readFloppyDisk(SUPER_BLOCK_POS, buffer);

    memCopy(buffer, sBlock, sizeof(superBlock));

    if(sBlock->code != FILESYSTEM_CODE){ // No hay filesystem creado
        printf("no esta montado\n");
        sBlock->code = FILESYSTEM_CODE; 
        sBlock->inodes = 1;
        for(int i = 0; i < FILESYSTEM_BITMAP_SIZE; i++){
            sBlock->bitMap[i] = 0;
        }
        sBlock->root = SUPER_BLOCK_POS+1;
        
        uint8 newSBlock[FLOPPY_BLOCK_SIZE];
        memCopy(sBlock, newSBlock, sizeof(superBlock));
        writeFloppyDisk(SUPER_BLOCK_POS, newSBlock); 
    }
}

uint32 getFreeBlock(){

    int freeBlock = -1;
    
    int i = 0;
    bool found = false;
    while( i < FILESYSTEM_BITMAP_SIZE && !found){
        if(sBlock->bitMap[i] != 0xFF){ // Si hay un bloque libre en esta parte del bitMap
            int j = 0;
            while(j < 8 && !found){ // Busco cual esta libre de los 8 de esta parte del bitMap
                if((sBlock->bitMap[i] & (1 << (7 - j))) == false){ 
                    freeBlock = i*8 + j;
                    sBlock->bitMap[i] = sBlock->bitMap[i] | (1 << 7-j); // Lo marco como en uso
                    found = true;
                }
                j++;
            }
        }
        i++;
    }

    if(freeBlock == -1)
        return freeBlock;

    freeBlock += SUPER_BLOCK_POS + 1;
    
    // Guardo el superBloque 
    uint8 newSBlock[FLOPPY_BLOCK_SIZE];
    memCopy(sBlock, newSBlock, sizeof(superBlock));
    writeFloppyDisk(SUPER_BLOCK_POS, newSBlock); 

    return freeBlock;
}

int mkdir(char name[FILE_NAME_SIZE]){

}