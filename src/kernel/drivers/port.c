#include "../libs/sdef.h"

byte8 port_byte_in (byte16 port){
    byte8 result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (byte16 port, byte8 data){
    asm volatile("out %%al, %%dx" : : "a" (data), "d" (port));
}

byte16 port_word_in (byte16 port){
    byte16 result;
    asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (byte16 port, byte16 data){
    asm volatile("out %%ax, %%dx" : : "a" (data), "d" (port));
}