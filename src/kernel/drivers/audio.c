#include "../libs/sdef.h"
#include "port.h"

static void play_sound(byte32 nFrequence){
    byte32 Div;
    byte8 tmp;
    Div = 1193180 / nFrequence;
    port_byte_out(0x43, 0xb6);
    port_byte_out(0x42, (byte8) (Div) );
    port_byte_out(0x42, (byte8) (Div >> 8));
    tmp = port_byte_in(0x61);
    if(tmp != (tmp | 3)) 
        port_byte_out(0x61, tmp | 3);
}
static void nosound(){
    byte8 tmp = port_byte_in(0x61) & 0xFC;

    port_byte_out(0x61, tmp);
}
void beep(){
    play_sound(1000);
    for(size t = 0; t < 999999999999; t++);
    nosound();
}