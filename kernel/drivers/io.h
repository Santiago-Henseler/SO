#ifndef IO_H
#define IO_H

// Headers extra
#include <stdint.h>

// Envia 1 byte al puerto I/O indicado
void outB(unsigned short port, unsigned char data);

// Recibe un byte del puerto indicado
uint8 inB(unsigned short port);

// Espera time (en microsegundos)
void ioWait(uint16 time);

#endif