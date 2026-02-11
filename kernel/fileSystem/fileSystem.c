#include "fileSystem.h"

typedef struct superBlock{
    uint32 code; 
    uint32 inodes; // Canitdad de inodes
    uint32 root;
    uint8 bitMap[FS_BITMAP_SIZE]; // 0 => bloque libre
} superBlock;

typedef struct dentry{
    char name[FILE_NAME_SIZE];
    uint16 inode;
} dentry;

typedef struct inode{
    fileType type;
    uint16 size;
    uint16 block[FILE_MAX_BLOCKS];
} inode;

static superBlock sb;
superBlock *sBlock = &sb;

inode *root;

int getFreeBlock(){
    int freeBlock = -1;
    
    int i = 0;
    bool found = false;
    while( i < FS_BITMAP_SIZE && !found){
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
    
    // Guardo la nueva info en el superBloque 
    writeFloppyDisk(SUPER_BLOCK_POS, sBlock); 

    return freeBlock;
}

inode * createInode(fileType type){
    inode * newInode = (inode *)malloc(sizeof(inode));
    if(newInode == NULL)
        return NULL;

    newInode->type = type;
    newInode->size = 0;

    return newInode;
}

inode * getInode(char * fileName){
    //TODO: Esto hay que hacerlo con el current directory
    inode * file = NULL;

    int i = 0;
    bool found = false;    

    while(!found && i < FILE_MAX_BLOCKS){
        uint8 buffer[FLOPPY_BLOCK_SIZE];

        if (root->block[i] < SUPER_BLOCK_POS)
            found = true; // no lo encontre pero ya no hay mas bloques validos 

        int err = readFloppyDisk(root->block[i], buffer);
        if(err == -1)
            return -1;

        dentry *entries = (dentry *)buffer;
        for(int j = 0; j < FS_DENTRY_BLOCK && !found; j++){
            dentry entrie = entries[j];
            if(strCompare(entrie.name, fileName)){
                readFloppyDisk(entrie.inode, buffer);
                memCopy(buffer, file, sizeof(inode));
                found = true;
            }
        }

        i++;
    }

    return file;
}

int createFile(fileType type, char * fileName){
    //TODO: Esto hay que hacerlo con el current directory
    int blockPos = getFreeBlock();
    if(blockPos == -1) goto error0;

    inode * newInode = createInode(type);
    if(newInode == NULL) goto error0;

    // Creo el dentry
    dentry newDentry;

    strCopy(fileName, newDentry.name);
    newDentry.inode = blockPos;

    // Guardo el dentry en el inodo tipo dir actual
    int dentryBlock = root->size / FLOPPY_BLOCK_SIZE;
    int dentryOffset = root->size % FLOPPY_BLOCK_SIZE;

    if(root->block[dentryBlock] == 0)
        root->block[dentryBlock] = getFreeBlock();

    uint8 dentryBuff[FLOPPY_BLOCK_SIZE];
    int floppyErr = readFloppyDisk(root->block[dentryBlock], dentryBuff);
    if(floppyErr == -1) goto error1;
    
    memCopy(&newDentry, dentryBuff + dentryOffset, sizeof(dentry));
    writeFloppyDisk(root->block[dentryBlock], dentryBuff);
    if(floppyErr == -1) goto error1;

    root->size += sizeof(dentry);
    
    floppyErr = writeFloppyDisk(blockPos, newInode);
    if(floppyErr == -1) goto error1;

    floppyErr = writeFloppyDisk(SUPER_BLOCK_POS+1, root);
    if(floppyErr == -1) goto error1;

    free(newInode);
    return 0;

    error1: free(newInode);
    error0: return -1;
}

void initFileSystem(){
    uint8 buffer[FLOPPY_BLOCK_SIZE];
    readFloppyDisk(SUPER_BLOCK_POS, buffer);

    memCopy(buffer, sBlock, sizeof(superBlock));

    if(sBlock->code != FS_CODE){ // No hay filesystem creado
        sBlock->code = FS_CODE; 
        sBlock->inodes = 1;
        for(int i = 0; i < FS_BITMAP_SIZE; i++){
            sBlock->bitMap[i] = 0;
        }
        sBlock->root = SUPER_BLOCK_POS+1;
        writeFloppyDisk(SUPER_BLOCK_POS, sBlock); 

        inode * newInode = createInode(DIR);
        getFreeBlock();
        writeFloppyDisk(SUPER_BLOCK_POS+1, newInode);
        root = newInode;
    }
}

int writeFile(char * fileName){

    if(fileName == NULL || strLen(fileName) >= FILE_NAME_SIZE)
        return -1;

    inode * file = getInode(fileName);
    if(file == NULL)
        return -1;
    if(file->type != DATA)
        return -1;
        
    int dataBlock  = file->size / FLOPPY_BLOCK_SIZE;
    int dataOffset = file->size % FLOPPY_BLOCK_SIZE;

    

}