#include "sdef.h"

size slen(char *str){
    size out = 0;
    for(; *str; str++, out++);
    return out;
}