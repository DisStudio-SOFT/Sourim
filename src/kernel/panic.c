#include "screen/text.h"
#include "libs/sdef.h"
#include "libs/string.h"

void panic(char *error){
    print("\nKernel panic!\nError:", RED, BLACK);
    print(error, LIGHT_CYAN, BLACK);
    asm("hlt");
}