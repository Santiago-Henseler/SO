#include "pic.h"

void unMask(int picNum){
    int port = (picNum >= 8) ? PIC_SECONDARY_PORT : PIC_PRIMARY_PORT;
    int num =  (picNum >= 8) ? picNum-8 : picNum; 

    uint8 mask = inB(port);
    outB(port, mask & -(1 << num));
}

void unMaskPic(){

    for(int i = 0; i < 16; i++){
        unMask(i);
    }
}

void mapPic(){

    // Habilito el modo de inicialización
    outB(PIC_PRIMARY_PORT, 0x11); 
    outB(PIC_SECONDARY_PORT, 0x11);

    // Mapeo las interrupciones de (0..7) al (32..39)
    outB(PIC_PRIMARY_DATA, 0x20); 
    // Mapeo las interrupciones de (8..15) al (40..47)
    outB(PIC_SECONDARY_DATA, 0x28);

    outB(PIC_PRIMARY_DATA, 0x4);
    outB(PIC_SECONDARY_DATA, 0x2);

    // Habilito el modo 8086
    outB(PIC_PRIMARY_DATA, 1);
    outB(PIC_SECONDARY_DATA, 1);

    // Limpio los registros
    outB(PIC_PRIMARY_DATA, 0);
    outB(PIC_SECONDARY_DATA, 0);

    unMaskPic();
}

void ackPic(int picNum){
    int port = (picNum >= 8) ? PIC_SECONDARY_PORT : PIC_PRIMARY_PORT;
    outB(port, 0x20);
}

