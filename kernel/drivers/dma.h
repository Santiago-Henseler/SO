#ifndef DMA_H
#define DMA_H

// Headers extra
#include <stdint.h>
#include "floppyDisk/floppy.h"
#include "io.h"

#define DMA_MASK 0x0A
#define DMA_CHANEL_2 0x04

#define DMA_WRITE 0x4A
#define DMA_READ 0x46

// Inicia el canal 2 para la transmision segun el modo indicado
void setupDMA(uint32 addr, int size, uint8 mode);

#endif