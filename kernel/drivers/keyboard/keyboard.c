#include "keyboard.h"

char keyCodeToChar(uint8 keyCode){

}

char getKeyInput(){
    uint8 keyCode = inB(KEYBOARD_DATA_PORT);

    if(keyCode == 30){
        return 'A';
    }

    return keyCode;

    return keyCodeToChar(keyCode);
} 
