#ifndef GCN_H
#define GCN_H

#include <stdint.h>

typedef enum Button {
    X = 0,
    A = 1,
    B = 2,
    Y = 3,
    L = 4,
    R = 5,
    //= 6,
    Z = 7,

    //      = 8,
    START   = 9,
    //      = 10,
    //      = 11
    D_UP    = 12,
    D_RIGHT = 13,
    D_DOWN  = 14,
    D_LEFT  = 15,
} eButton;

// [X A B Y L R ZL? ZR] [_ Start _ _ DU DR DD DL]
typedef struct Buttons {
    uint8_t X : 1;
    uint8_t A : 1;
    uint8_t B : 1;
    uint8_t Y : 1;
    uint8_t L : 1;
    uint8_t R : 1;
    uint8_t   : 1;
    uint8_t Z : 1;

    uint8_t       : 1;
    uint8_t Start : 1;
    uint8_t       : 1;
    uint8_t       : 1;
    uint8_t DUp   : 1;
    uint8_t DRight: 1;
    uint8_t DDown : 1;
    uint8_t DLeft : 1;
} Buttons;

// [LR Axis] [UD Axis] - Main Stick
typedef struct MainStick {
    unsigned char LR;
    unsigned char UD;
} MainStick;

// [UD Axis] [LR Axis] - C Stick
typedef struct CStick {
    unsigned char UD;
    unsigned char LR;
} CStick;

// [Left Trigger] [Right Trigger]
typedef struct Triggers {
    unsigned char Left;
    unsigned char Right;
} Triggers;

// Buttons[2], MainStick[2], CStick[2], Triggers[2], Mystery[1]
typedef struct GameCube {
    Buttons buttons; // 1
    MainStick mainStick; // 2
    CStick cStick; // 2
    Triggers triggers; // 2
    char : 8;
} GameCube;

char getButton(GameCube* gc, eButton button);

void printGameCube(GameCube *gc);

void printButtons(GameCube *gc);
void printMainStick(GameCube *gc);
void printCStick(GameCube *gc);
void printTriggers(GameCube *gc);

#endif