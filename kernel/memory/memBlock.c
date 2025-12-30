#include "memBlock.h"

#include "../lib/stdio.h"

void initMemBlock(uint32 memSize){

    void * blockDir = (void * )0x0; 

    for(int i = 0; i < 10; i++){
        printf("%x y guardo un %i\n", blockDir+i*4096, i);

        int * dir = blockDir+i*4096;
        *dir = i;
    }

    for(int i = 0; i < 10; i++){

        int * dir = blockDir+i*4096;

        printf("%x y guarde un %i\n", dir, *dir);

    }


}