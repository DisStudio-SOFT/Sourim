#include "../kernel/screen/text.h"
#include "../kernel/panic.h"
#include "../kernel/drivers/power.h"

void kmain(){
    clear();
    print("Hello, world!!!", LIGHT_GREY, BLACK);
}

void boot(){
    detect_screen();
    kmain();
}