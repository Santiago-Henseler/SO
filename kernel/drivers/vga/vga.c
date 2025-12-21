#include "vga.h"

#define VIDEOMEM ((char*) 0xB8000)

int cursorX = 0;
int cursorY = 0;

void moveCursor(int pos){

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

void printVga(int color, char* str){
    while (*str)
    {
        if(*str == '\n'){
            str++;
            newLineVga();
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

    moveCursor(cursorX + VGA_WIDTH*cursorY);
    return;
}

void newLineVga(){

    if(cursorY < VGA_HEIGHT-1){
        cursorY++;
        cursorX = 0;
    }else{
        scrollUpVga();
        cursorX = 0;
    }

    moveCursor(cursorX + VGA_WIDTH*cursorY);

    return;
}

void scrollUpVga(){
   
    for(int y = 0; y < VGA_HEIGHT-1; y++){
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
    
    moveCursor(0);

    return;
}