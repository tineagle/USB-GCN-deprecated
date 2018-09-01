#include <stdio.h>

typedef struct Buttons {
    char X : 1;
    char A : 1;
    char B : 1;
    char Y : 1;
    char L : 1;
    char R : 1;
    char : 1;
    char Z : 1;

    char : 1;
    char S : 1;
    char : 1;
    char : 1;
    char DUp : 1;
    char DRight : 1;
    char DDown : 1;
    char DLeft : 1;
} Buttons;

typedef struct MainStick {
    unsigned char LR;
    unsigned char UD;
} MainStick;

typedef struct CStick {
    unsigned char UD;
    unsigned char LR;
} CStick;

typedef struct Bumpers {
    unsigned char Left;
    unsigned char Right;
} Bumpers;

typedef struct GameCube {
    Buttons buttons; // 1
    MainStick mainStick; // 2
    CStick cStick; // 2
    Bumpers bumpers; // 2
    char : 8;
} GameCube;

#define PRINT_BUTTON(NAME) if(buttons.NAME) printf("" #NAME); else printf("-")

void printButtons(GameCube *gc) {
    Buttons buttons = gc->buttons;
    PRINT_BUTTON(A);
    PRINT_BUTTON(B);
    PRINT_BUTTON(Y);
    PRINT_BUTTON(X);
    PRINT_BUTTON(Z);
    PRINT_BUTTON(S);
    PRINT_BUTTON(L);
    PRINT_BUTTON(R);
    printf(" | ");

    if(buttons.DUp) printf("^"); else printf("-");
    if(buttons.DDown) printf("V"); else printf("-");
    if(buttons.DLeft) printf("<"); else printf("-");
    if(buttons.DRight) printf(">");else printf("-");
    printf(" | ");
}

void printMainStick(GameCube *gc) {
    if(gc->mainStick.LR == 128)  printf("M-- :     ");
    if(gc->mainStick.LR < 128)   printf("M-< : %03hhu ", 128 - gc->mainStick.LR);
    if(gc->mainStick.LR > 128)   printf("M-> : %03hhu ", gc->mainStick.LR - 128);
    if(gc->mainStick.UD == 0)    printf("M-| :     ");
    if(gc->mainStick.UD < 128)   printf("M-^ : %03hhu ", 128 - gc->mainStick.UD);
    if(gc->mainStick.UD > 128)   printf("M-V : %03hhu ", gc->mainStick.UD - 128);
    printf("| ");
}

void printCStick(GameCube *gc) {
    if(gc->cStick.LR == 128)  printf("C-- :     ");
    if(gc->cStick.LR < 128)   printf("C-< : %03hhu ", 128 - gc->cStick.LR);
    if(gc->cStick.LR > 128)   printf("C-> : %03hhu ", gc->cStick.LR - 128);
    if(gc->cStick.UD == 128)  printf("C-| :     ");
    if(gc->cStick.UD < 128)   printf("C-^ : %03hhu ", 128 - gc->cStick.UD);
    if(gc->cStick.UD > 128)   printf("C-V : %03hhu ", gc->cStick.UD - 128);
    printf("| ");
}

void printBumpers(GameCube *gc) {
    printf("LB : %3hhu ", gc->bumpers.Left);
    printf("RB : %3hhu ", gc->bumpers.Right);
}

void printGamecube(GameCube *gc) {
    printButtons(gc);
    printMainStick(gc);
    printCStick(gc);
    printBumpers(gc);
    printf("\n");
}

void printBits(char c) {
    for(char i = 0; i < 8; ++i) {
        char bit = (c >> (7 - i)) & 0x1;
        printf("%d", bit);
    }
}

int main() {
    printf("%d\n", sizeof(struct GameCube));

    FILE* f = fopen("/dev/hidraw2", "r");

    GameCube gc;
    while(1) {
        fread(&gc, 9, 1, f);
        for(int i = 0; i < 9; ++i) {
            printGamecube(&gc);
        }
    }

    fclose(f);
}

// Bit order is flipped within bytes
// [ZR ZL R L Y B A X] [DL DD DR DU ? ? Start ?]
// [LR Axis] [UD Axis] - Main Stick
// [UD Axis] [LR Axis] - C Stick
// [Left Bumper] [Right Bumper]
// [Some D-Pad Shit]