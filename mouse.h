#ifndef MOUSE_H
#define MOUSE_H

typedef struct Mouse Mouse;

Mouse* createMouse();
void destroyMouse(Mouse* mouse);

#define MOUSE_EMPTY_FUN(NAME) void NAME(Mouse* mouse)
#define MOUSE_STATE_FUN(NAME) void NAME(Mouse* mouse, int state)
#define MOUSE_COORD_FUN(NAME) void NAME(Mouse* mouse, int x, int y)

MOUSE_EMPTY_FUN(sendEvents);

MOUSE_STATE_FUN(leftClick);
MOUSE_STATE_FUN(rightClick);
MOUSE_STATE_FUN(middleClick);
MOUSE_STATE_FUN(forwardClick);
MOUSE_STATE_FUN(backClick);

MOUSE_STATE_FUN(upArrow);
MOUSE_STATE_FUN(rightArrow);
MOUSE_STATE_FUN(downArrow);
MOUSE_STATE_FUN(leftArrow);

MOUSE_COORD_FUN(moveMouse);
MOUSE_COORD_FUN(scrollMouse);

#endif