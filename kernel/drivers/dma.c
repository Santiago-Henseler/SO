#include "dma.h"

void setupDMA(uint32 addr, int size, uint8 mode){
    outB(DMA_MASK, 0x06);        
    outB(0x0C, 0xFF);        

    outB(DMA_CHANEL_2, addr & 0xFF);
    outB(DMA_CHANEL_2, (addr >> 8) & 0xFF);
    outB(0x81, (addr >> 16) & 0xFF);

    uint16 count = size - 1;
    outB(0x05, count & 0xFF);
    outB(0x05, count >> 8);

    outB(0x0B, mode); 
    outB(DMA_MASK, 0x02);
}