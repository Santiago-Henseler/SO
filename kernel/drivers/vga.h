#ifndef VGA_H
#define VGA_H

// Colors definition
#define BLACK 0
#define BLUE  1
#define GREEN 2
#define RED   4


void printVga(int color, char* str);

void clearVga(void);

void newLineVga(void);

void scrollUpVga(void);

#endif