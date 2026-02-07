#include "io.h"

void ioWait(uint16 time){
    for (int i = 0; i < time*25; i++)
        inB(0x80);
}