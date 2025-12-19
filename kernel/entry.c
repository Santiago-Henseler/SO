#define VIDEOMEM ((char*) 0xB8000) // [0xB8000:] 

int print(int color, char* str);

void main(){

    char s[] = "hoooola\0";


    volatile char * videoMem =  VIDEOMEM;

    int c = 4;

    print(c, s);

    for (;;);
}

int print(int color, char* str){

    volatile char * videoMem =  VIDEOMEM;

    while (*str)
    {
        videoMem[0] = *str++;
        videoMem[1] = color; 

        videoMem +=2;
    }

    return 0;
}
