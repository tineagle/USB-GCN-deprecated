#include "gcn.h"
#include "usb.h"

#include <stdio.h>

int main() {
    printf("%d\n", sizeof(struct GameCube));

    FILE* f = fopen("/dev/hidraw2", "r");

    GameCube gc;
    while(1) {
        fread(&gc, 9, 1, f);
        for(int i = 0; i < 9; ++i) {
            printGameCube(&gc);
        }
    }

    fclose(f);
}