#include "keyboard.h"

bool mayusc = false;

// Las keycodes que estan en 0 todavia no estan implementadas
// Y solo esta implementado keyDown
char keyCodeMin[58] = {
    // TODO: terminar de implementar todas las teclas (vale la pena?)
    0,0,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,0,0,KEY_BACK,KEY_TAB,
    KEY_q,KEY_w,KEY_e,KEY_r,KEY_t,KEY_y,KEY_u,KEY_i,KEY_o,KEY_p,0,0,KEY_ENTER,0,
    KEY_a,KEY_s,KEY_d,KEY_f,KEY_g,KEY_h,KEY_j,KEY_k,KEY_l,KEY_ñ,0,0,0,0,
    KEY_z,KEY_x,KEY_c,KEY_v,KEY_b,KEY_n,KEY_m,0,0,0,0,0,0,KEY_ESPACIO
};

char keyCodeToChar(uint8 keyCode){
    if(keyCode == KEY_MAYS_DER_D || keyCode == KEY_MAYS_IZQ_D) // TODO: el bloqMays deberia existir
        mayusc = true;

    if(keyCode == KEY_MAYS_IZQ_U || keyCode == KEY_MAYS_DER_U)
        mayusc = false;

    if(mayusc && keyCode == 39) 
        return KEY_ñ +1;

    if(keyCode > 60)                   // TODO: No le doy bola a las keyDown
        return 0; 

    char key = keyCodeMin[keyCode];

    if(mayusc && (key >= KEY_a && key <= KEY_z))
        key -= 32;                    // Resto 32 porque es la distancia de las minusculas a las mayusculas en ascii

    return key;
}

char getKeyInput(){
    uint8 keyCode = inB(KEYBOARD_DATA_PORT);

    return keyCodeToChar(keyCode);
} 
