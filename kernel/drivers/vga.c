#include "vga.h"

#define VIDEOMEM ((char*) 0xB8000)

#define WIDTH 80
#define HEIGHT 25

int cursorX = 0;
int cursorY = 0;

void printVga(int color, char* str){

    while (*str)
    {
        if(*str == '\n'){
            *str++;
            newLineVga();
            continue;
        }

        volatile char * videoMem = VIDEOMEM + 2*cursorX + 160*cursorY;

        videoMem[0] = *str++;
        videoMem[1] = color; 

        cursorX++;
        if(cursorX == WIDTH){
            cursorX = 0;
            cursorY++;
        }
        if(cursorY == HEIGHT)
            scrollUpVga();

    }
    return;
}

void newLineVga(){

    if(cursorY < HEIGHT-1){
        cursorY++;
        cursorX = 0;
    }else{
        scrollUpVga();
        cursorX = 0;
    }

    return;
}

void scrollUpVga(){
   
    for(int y = 0; y < HEIGHT-1; y++){
        for(int x = 0; x < WIDTH; x++){
            volatile char * videoMem = VIDEOMEM + 2*x + 160*y;
            volatile char * videoMemOld = VIDEOMEM + 2*x + 160*(y+1);
            videoMem[0] = videoMemOld[0];
            videoMem[1] = videoMemOld[1]; //TODO: chequear anda medio raro el paso de formato
        }
    }

    return;
}

void clearVga(){
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            volatile char * videoMem = VIDEOMEM + 2*x + 160*y;
            videoMem[0] = ' ';
            videoMem[1] = GREEN;
        }
    }
    
    cursorX = 0;
    cursorY = 0;

    return;
}
