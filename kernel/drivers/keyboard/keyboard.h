#ifndef KEYBOARD_H
#define KEYBOARD_H

// Headers extra
#include "../../lib/stdint.h"
#include "../../lib/stdbool.h"
#include "../../lib/ascii.h"

// Keyboard Port
#define KEYBOARD_DATA_PORT 0x60

// Devuelve el char leido por el teclado
char getKeyInput();

#endif