#include "gcn.h"

#include <stdio.h>

#define PRINT_BUTTON(BUTTON, NAME) if(buttons.BUTTON) printf(""NAME); else printf("-")

void printButtons(GameCube *gc) {
    Buttons buttons = gc->buttons;
    PRINT_BUTTON(A, "A");
    PRINT_BUTTON(B, "B");
    PRINT_BUTTON(Y, "Y");
    PRINT_BUTTON(X, "X");
    PRINT_BUTTON(Z, "Z");
    PRINT_BUTTON(Start, "S");
    PRINT_BUTTON(L, "L");
    PRINT_BUTTON(R, "R");

    printf(" | ");

    PRINT_BUTTON(DUp, "^");
    PRINT_BUTTON(DDown, "V");
    PRINT_BUTTON(DLeft, "<");
    PRINT_BUTTON(DRight, ">");
}

void printMainStick(GameCube *gc) {
    if(gc->mainStick.LR == 128)  printf("M-- :     ");
    if(gc->mainStick.LR < 128)   printf("M-< : %03hhu ", 128 - gc->mainStick.LR);
    if(gc->mainStick.LR > 128)   printf("M-> : %03hhu ", gc->mainStick.LR - 128);
    if(gc->mainStick.UD == 0)    printf("M-| :     ");
    if(gc->mainStick.UD < 128)   printf("M-^ : %03hhu ", 128 - gc->mainStick.UD);
    if(gc->mainStick.UD > 128)   printf("M-V : %03hhu ", gc->mainStick.UD - 128);
}

void printCStick(GameCube *gc) {
    if(gc->cStick.LR == 128)  printf("C-- :     ");
    if(gc->cStick.LR < 128)   printf("C-< : %03hhu ", 128 - gc->cStick.LR);
    if(gc->cStick.LR > 128)   printf("C-> : %03hhu ", gc->cStick.LR - 128);
    if(gc->cStick.UD == 128)  printf("C-| :     ");
    if(gc->cStick.UD < 128)   printf("C-^ : %03hhu ", 128 - gc->cStick.UD);
    if(gc->cStick.UD > 128)   printf("C-V : %03hhu ", gc->cStick.UD - 128);
}

void printTriggers(GameCube *gc) {
    printf("LT : %03hhu ", gc->triggers.Left);
    printf("RT : %03hhu ", gc->triggers.Right);
}

void printGameCube(GameCube *gc) {
    printButtons(gc);
    printf(" | ");
    printMainStick(gc);
    printf(" | ");
    printCStick(gc);
    printf(" | ");
    printTriggers(gc);
    printf("\n");
}