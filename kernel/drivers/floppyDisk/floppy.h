#ifndef FLOPPY_H
#define FLOPPY_H

// Headers extra
#include "../io.h"
#include <stdint.h>

#define FLOPPY_DATA_PORT 0x3F5
#define FLOPPY_DIGITAL_OUTPUT_PORT 0x3F2 

#define FLOPPY_VERSION_COMMAND 16
#define FLOPPY_CONFIGURE_COMMAND 19
#define FLOPPY_LOCK_COMMAND 0x94

void initFloppyDisk();

#endif