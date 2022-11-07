#include "../libs/sdef.h"
#include "port.h"

#define check_flag(flags, n) ( (flags) & 1<<(n) )

void reboot(){
    byte8 v;
    asm volatile ("cli");
    do{
        v = port_byte_in(0x64);
        if(check_flag(v, 0) != 0)
            port_byte_in(0x60);
    } while(check_flag(v, 1) != 0);
    port_byte_out(0x64, 0xfe);
    loop:
        asm volatile ("hlt");
        goto loop;
}
void shutdown(){
    port_word_out(0xB004, 0x2000);
    port_word_out(0x604, 0x2000);
    port_word_out(0x4004, 0x3400);
}