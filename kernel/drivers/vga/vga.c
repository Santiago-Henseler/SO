#include "vga.h"

#define VIDEOMEM ((char*) 0xB8000)

int cursorX = 0;
int cursorY = 0;

void moverCursor(int pos){

    if (pos < 0)
        pos = 0;
    else
        pos = pos % (VGA_HEIGHT*VGA_WIDTH);

    // Seteo para enviar parte alta de pos y lo envio
    outB(COMMAND_PORT_VGA, 14); 
    outB(DATA_PORT_VGA, ((pos >> 8) & 0x00FF));
    // Seteo para enviar parte baja de pos y lo envio
    outB(COMMAND_PORT_VGA, 15);
    outB(DATA_PORT_VGA, pos & 0x00FF);

    return;
}

void printVga(const char* str, int color){
    while (*str)
    {
        if(*str == KEY_ENTER){
            newLineVga();
            str++;
            continue;
        }else if(*str == KEY_TAB){
            for(int i = 0; i < 4; i++)
                lineVacia(color);
            str++;
            continue;
        }else if(*str == KEY_ESPACIO){
            lineVacia(color);
            str++;
            continue;
        }

        volatile char * videoMem = VIDEOMEM + 2*(cursorX + VGA_WIDTH*cursorY);

        videoMem[0] = *str++;
        videoMem[1] = color; 

        cursorX++;
        if(cursorX == VGA_WIDTH){
            cursorX = 0;
            cursorY++;
        }
        if(cursorY == VGA_HEIGHT)
            scrollUpVga();
    }

    moverCursor(cursorX + VGA_WIDTH*cursorY);
    return;
}

void lineVacia(int color){
    volatile char * videoMem = VIDEOMEM + 2*(cursorX + VGA_WIDTH*cursorY);
    videoMem[0] = ' ';
    videoMem[1] = color;
    cursorX++;
}

void newLineVga(){

    if(cursorY < VGA_HEIGHT-1){
        cursorY++;
        cursorX = 0;
    }else{
        scrollUpVga();
        cursorX = 0;
    }

    moverCursor(cursorX + VGA_WIDTH*cursorY);

    return;
}

void scrollUpVga(){
   
    for(int y = 0; y < VGA_HEIGHT; y++){
        for(int x = 0; x < VGA_WIDTH; x++){
            volatile char * videoMem = VIDEOMEM + 2*(x + VGA_WIDTH*y);
            volatile char * videoMemOld = VIDEOMEM +2*(x + VGA_WIDTH*(y+1));
            videoMem[0] = videoMemOld[0];
            videoMem[1] = videoMemOld[1]; //TODO: chequear anda medio raro el paso de formato
        }
    }

    return;
}

void clearVga(){
    for(int y = 0; y < VGA_HEIGHT; y++){
        for(int x = 0; x < VGA_WIDTH; x++){
            volatile char * videoMem = VIDEOMEM + 2*x + 160*y;
            videoMem[0] = ' ';
            videoMem[1] = WHITE;
        }
    }
    
    cursorX = 0;
    cursorY = 0;
    
    moverCursor(0);

    return;
}