#include "floppy.h"

#define FLOPPY_DMA_ADDR  0x1000  

uint8* floppyDmaBuffer = (uint8*)FLOPPY_DMA_ADDR;
bool floppyInterrupt = false;

void setFloppyInt(){
    floppyInterrupt = true;
}

void waitFloppyInt(){
    while(!floppyInterrupt)
        continue;

    floppyInterrupt = false;
}

uint8 reciveFloppyCommand(){

    bool available = false;

    while (!available) {
        uint8 msr = inB(FLOPPY_STATUS_PORT);
        if ((msr & 0x80) && (msr & 0x40))
            available = true;
    }

    return inB(FLOPPY_DATA_PORT);
}

void sendFloppyCommand(uint8 command){

    bool available = false;

    while (!available) {
        uint8 msr = inB(FLOPPY_STATUS_PORT);
        if ((msr & 0x80) && !(msr & 0x40))
            available = true;
    }

    outB(FLOPPY_DATA_PORT, command);
}

void floppySeek(uint8 cylinder, uint8 head) {
    floppyInterrupt = false;

    sendFloppyCommand(FLOPPY_SEEK_COMMAND);
    sendFloppyCommand((head << 2) | 0);
    sendFloppyCommand(cylinder);

    waitFloppyInt();

    sendFloppyCommand(FLOPPY_SENSE_COMMAND);
    reciveFloppyCommand();  
    reciveFloppyCommand(); 
}

int floppyDiskAction(int blockNum, uint8 buffer[FLOPPY_BLOCK], bool write){

    if(write)
        memCopy(buffer, floppyDmaBuffer, FLOPPY_BLOCK);

    setupDMA(floppyDmaBuffer, FLOPPY_BLOCK, write ? DMA_WRITE : DMA_READ);

    uint8 head = (blockNum / 18) % 2;;
    uint8 cylinder = blockNum / 36;
    uint8 sector = (blockNum % 18) + 1;

    floppySeek(cylinder, head);

    // Indico que voy a escribir
    sendFloppyCommand(write ? (FLOPPY_MT | FLOPPY_MFM | 0x5) : (FLOPPY_MT | FLOPPY_MFM | 0x6 ));

    sendFloppyCommand((head << 2) | 0); // ver driver number (el 0)
    sendFloppyCommand(cylinder);
    sendFloppyCommand(head);
    sendFloppyCommand(sector);
    sendFloppyCommand(2);
    sendFloppyCommand(18);
    sendFloppyCommand(0x1B);
    sendFloppyCommand(0xFF);

    waitFloppyInt(); 

    uint8 st0 = reciveFloppyCommand();
    uint8 st1 = reciveFloppyCommand();
    uint8 st2 = reciveFloppyCommand();
    reciveFloppyCommand();
    reciveFloppyCommand();
    reciveFloppyCommand();
    reciveFloppyCommand();

    if ((st0 & 0xC0) != 0) return -1;
    if (st1 | st2) return -1;

    if(!write)
        memCopy(floppyDmaBuffer, buffer, FLOPPY_BLOCK);

    return 0;
}

int writeFloppyDisk(int blockNum, uint8 buffer[FLOPPY_BLOCK]){
    return floppyDiskAction(blockNum, buffer, true); 
}

int readFloppyDisk(int blockNum, uint8 buffer[FLOPPY_BLOCK]){
    return floppyDiskAction(blockNum, buffer, false);
}

void initFloppyDisk(){

    sendFloppyCommand(FLOPPY_VERSION_COMMAND);
    uint8 version = reciveFloppyCommand();

    if(version != 0x90)
        for(;;); //TODO: No hay soporte para esta unidad floppy

    // Configuro el floppy disk
    sendFloppyCommand(FLOPPY_CONFIGURE_COMMAND);
    sendFloppyCommand(0x68);   // Busqueda implicita habilitada              
    sendFloppyCommand(0x0F);   // FIFO habilitado
    sendFloppyCommand(0x00);   // Uso de valor predeterminado de compresion

    // Mantener la configuracion en el floppy
    sendFloppyCommand(FLOPPY_LOCK_COMMAND);

    // Reset Floppy driver
    outB(FLOPPY_DIGITAL_OUTPUT_PORT, 0x00);
    outB(FLOPPY_DIGITAL_OUTPUT_PORT, 0x0c);
    outB(FLOPPY_DIGITAL_OUTPUT_PORT, 0x1C);

    waitFloppyInt();

    // Recalibro el Floppy
    sendFloppyCommand(FLOPPY_RECALIBRATE_COMMAND);
    sendFloppyCommand(0x00); 
    sendFloppyCommand(FLOPPY_SENSE_COMMAND); 
    reciveFloppyCommand();
    reciveFloppyCommand(); 
}