#ifndef PIC_H
#define PIC_H

// Headers extra
#include "../drivers/io.h"

// Port de comando y estado del pic
#define PIC_PRIMARY_PORT 0x20  
// Port de mascara de interrupcion del pic
#define PIC_PRIMARY_DATA 0x21

// Port de comando y estado del pic
#define PIC_SECONDARY_PORT 0x20  
// Port de mascara de interrupcion del pic
#define PIC_SECONDARY_DATA 0x21

// Mapeo las interrupciones por hardwarer a la IDT
void mapPic();

#endif