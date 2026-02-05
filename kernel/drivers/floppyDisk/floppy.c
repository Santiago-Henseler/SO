#include "floppy.h"

#include <stdio.h>

void initFloppyDisk(){

    outB(FLOPPY_DATA_PORT, FLOPPY_VERSION_COMMAND);
    uint8 version = inB(FLOPPY_DATA_PORT);

    if(version != 0x90)
        for(;;); //TODO: No hay soporte para esta unidad floppy

    // Configuro el floppy disk
    outB(FLOPPY_DATA_PORT, FLOPPY_CONFIGURE_COMMAND);
    outB(FLOPPY_DATA_PORT, 0x0);   // Busqueda implicita habilitada              
    outB(FLOPPY_DATA_PORT, 0x57);  // FIFO habilitado
    outB(FLOPPY_DATA_PORT, 0x0);   // Uso de valor predeterminado de compresion

    // Mantener la configuracion
    outB(FLOPPY_DATA_PORT, FLOPPY_LOCK_COMMAND);


}