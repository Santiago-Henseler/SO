#ifndef FLOPPY_H
#define FLOPPY_H

// Headers extra
#include <stdint.h>
#include <stdbool.h>
#include <stdmem.h>
#include "../io.h"
#include "../dma.h"

#define FLOPPY_BLOCK 512

#define FLOPPY_DATA_PORT 0x3F5
#define FLOPPY_STATUS_PORT 0x3F4
#define FLOPPY_DIGITAL_OUTPUT_PORT 0x3F2 

#define FLOPPY_VERSION_COMMAND 16
#define FLOPPY_CONFIGURE_COMMAND 19
#define FLOPPY_LOCK_COMMAND 0x94
#define FLOPPY_SEEK_COMMAND 0x0F
#define FLOPPY_SENSE_COMMAND 0x08
#define FLOPPY_RECALIBRATE_COMMAND 0x07

#define FLOPPY_MT 0x80
#define FLOPPY_MFM 0x40

// Inicia el floppy disk 
void initFloppyDisk();

// Indica que se recibio una interrupcion por parte del floppy
void setFloppyInt();

// Permite escribir un bloque de memoria en el floppy disk
int writeFloppyDisk(int blockNum, uint8 buffer[FLOPPY_BLOCK]);

// Permite leer un bloque de memoria del floppy disk
int readFloppyDisk(int blockNum, uint8 buffer[FLOPPY_BLOCK]);

#endif