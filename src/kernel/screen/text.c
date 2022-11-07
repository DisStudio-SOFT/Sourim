#include "../libs/sdef.h"
#include "../drivers/port.h"
#include "../panic.h"

enum color {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GREY = 7,
	DARK_GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN = 14,
	WHITE = 15,
};
enum SCREEN_TYPE
{
    SCREEN_TYPE_COLOUR = 0x20,
    SCREEN_TYPE_MONOCHROME = 0x30,
};
byte8 *sscreen = (byte8*) 0xb8000;
byte8 *screen; 
void detect_screen(){
    const byte16* bda_detected_hardware_ptr = (const byte16*) 0x410;
    byte16 type = *bda_detected_hardware_ptr & 0x30;
	switch(type){
		case SCREEN_TYPE_COLOUR:
			sscreen = screen = (byte8*) 0xb8000;
			break;
		case SCREEN_TYPE_MONOCHROME:
			sscreen = screen = (byte8*) 0xb0000;
			break;
		default:
			panic("8000");
			break;
	}
}
size screenpos = 0;
size ycur = 0;
size xcur = 0;

void updatecur(){
	byte16 pos = ycur * 80 + xcur;
	port_word_out(0x3D4, 0x0F);
	port_word_out(0x3D5, (byte8) (pos & 0xFF));
	port_word_out(0x3D4, 0x0E);
	port_word_out(0x3D5, (byte8) ((pos >> 8) & 0xFF));
}
void putchar(char ch, enum color fg, enum color bg){
	if(ch == '\n'){
		for(size pos = xcur; pos < 80; pos++){
			screen[screenpos++] = 0;
			screen[screenpos++] = 0x07;
		}
		xcur = 0;
		ycur++;
	} else {
		screen[screenpos++] = ch;
		screen[screenpos++] = fg | bg << 4;
		xcur++;
		if(xcur == 80){
			xcur = 0;
			ycur++;
		}
	}
    updatecur();
}
void clear(){
	screen = (byte8*) 0xb8000;
	screenpos = 0;
	for(size pos = 0; pos < 80 * 15 * 2; pos++)
		putchar(0, LIGHT_GREY, BLACK);
	screen = (byte8*) 0xb8000;
	screenpos = 0;
	xcur = 0;
}
void print(char *str, enum color fg, enum color bg){
    for(; *str; str++)
        putchar(*str, fg, bg);
}