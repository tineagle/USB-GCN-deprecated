#include "usb.h"

#include <stdio.h>

void printBits(char c) {
    for(char i = 0; i < 8; ++i) {
        char bit = (c >> (7 - i)) & 0x1;
        printf("%d", bit);
    }
}