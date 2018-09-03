#ifndef GCN_H
#define GCN_H

// [X A B Y L R ZL? ZR] [_ Start _ _ DU DR DD DL]
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
    char Start : 1;
    char : 1;
    char : 1;
    char DUp : 1;
    char DRight : 1;
    char DDown : 1;
    char DLeft : 1;
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

void printGameCube(GameCube *gc);

void printButtons(GameCube *gc);
void printMainStick(GameCube *gc);
void printCStick(GameCube *gc);
void printTriggers(GameCube *gc);

#endif