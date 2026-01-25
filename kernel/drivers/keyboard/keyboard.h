#ifndef KEYBOARD_H
#define KEYBOARD_H

// Headers extra
#include <stdint.h>
#include <stdbool.h>
#include <ascii.h>
#include "../io.h"

// Keyboard Port
#define KEYBOARD_DATA_PORT 0x60

// Devuelve el char leido por el teclado
char getKeyInput();

#endif