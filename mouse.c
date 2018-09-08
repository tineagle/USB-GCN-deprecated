#include "mouse.h"

#include "linux/uinput.h"

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct Mouse {
    int fd;
} Mouse;

void setupMouseFeatures(Mouse* mouse);
void emit(int fd, int type, int code, int val);

Mouse* createMouse() {
    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    Mouse* mouse = malloc(sizeof(Mouse));
    mouse->fd = fd;

    struct uinput_setup usetup;
    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    strcpy(usetup.name, "GCN 1");

    setupMouseFeatures(mouse);

    ioctl(mouse->fd, UI_DEV_SETUP, &usetup);
    ioctl(mouse->fd, UI_DEV_CREATE);

    return mouse;
}

void destroyMouse(Mouse* mouse) {
    ioctl(mouse->fd, UI_DEV_DESTROY);
    close(mouse->fd);
    free(mouse);
}

void setupMouseFeatures(Mouse* mouse) {
    ioctl(mouse->fd, UI_SET_EVBIT, EV_KEY);
    ioctl(mouse->fd, UI_SET_KEYBIT, BTN_LEFT);
    ioctl(mouse->fd, UI_SET_KEYBIT, BTN_RIGHT);
    ioctl(mouse->fd, UI_SET_KEYBIT, BTN_MIDDLE);
    ioctl(mouse->fd, UI_SET_KEYBIT, BTN_EXTRA);
    ioctl(mouse->fd, UI_SET_KEYBIT, BTN_SIDE);
    
    ioctl(mouse->fd, UI_SET_KEYBIT, KEY_UP);
    ioctl(mouse->fd, UI_SET_KEYBIT, KEY_RIGHT);
    ioctl(mouse->fd, UI_SET_KEYBIT, KEY_DOWN);
    ioctl(mouse->fd, UI_SET_KEYBIT, KEY_LEFT);

    ioctl(mouse->fd, UI_SET_KEYBIT, KEY_TAB);
    ioctl(mouse->fd, UI_SET_KEYBIT, KEY_ENTER);
    
    ioctl(mouse->fd, UI_SET_KEYBIT, KEY_LEFTCTRL);
    ioctl(mouse->fd, UI_SET_KEYBIT, KEY_LEFTSHIFT);
    ioctl(mouse->fd, UI_SET_KEYBIT, KEY_LEFTALT);


    ioctl(mouse->fd, UI_SET_EVBIT, EV_REL);
    ioctl(mouse->fd, UI_SET_RELBIT, REL_X);
    ioctl(mouse->fd, UI_SET_RELBIT, REL_Y);
    ioctl(mouse->fd, UI_SET_RELBIT, REL_WHEEL);
    ioctl(mouse->fd, UI_SET_RELBIT, REL_HWHEEL);
}

void emit(int fd, int type, int code, int val) {
   struct input_event ie;
   memset(&ie, 0, sizeof(ie));

   ie.type = type;
   ie.code = code;
   ie.value = val;

   write(fd, &ie, sizeof(ie));
}

MOUSE_EMPTY_FUN(sendEvents) {
    emit(mouse->fd, EV_SYN, SYN_REPORT, 0);
}

MOUSE_STATE_FUN(leftClick) {
    emit(mouse->fd, EV_KEY, BTN_LEFT, state);
}

MOUSE_STATE_FUN(rightClick) {
    emit(mouse->fd, EV_KEY, BTN_RIGHT, state);
}

MOUSE_STATE_FUN(middleClick) {
    emit(mouse->fd, EV_KEY, BTN_MIDDLE, state);
}

MOUSE_STATE_FUN(forwardClick) {
    emit(mouse->fd, EV_KEY, BTN_EXTRA, state);
}

MOUSE_STATE_FUN(backClick) {
    emit(mouse->fd, EV_KEY, BTN_SIDE, state);
}

MOUSE_STATE_FUN(upArrow) {
    emit(mouse->fd, EV_KEY, KEY_UP, state);
}

MOUSE_STATE_FUN(rightArrow) {
    emit(mouse->fd, EV_KEY, KEY_RIGHT, state);
}

MOUSE_STATE_FUN(downArrow) {
    emit(mouse->fd, EV_KEY, KEY_DOWN, state);
}

MOUSE_STATE_FUN(leftArrow) {
    emit(mouse->fd, EV_KEY, KEY_LEFT, state);
}

MOUSE_STATE_FUN(ctrlKey) {
    emit(mouse->fd, EV_KEY, KEY_LEFTCTRL, state);
}

MOUSE_STATE_FUN(shiftKey) {
    emit(mouse->fd, EV_KEY, KEY_LEFTSHIFT, state);
}

MOUSE_STATE_FUN(altKey) {
    emit(mouse->fd, EV_KEY, KEY_LEFTALT, state);
}

MOUSE_STATE_FUN(tabKey) {
    emit(mouse->fd, EV_KEY, KEY_TAB, state);
}

MOUSE_STATE_FUN(enterKey) {
    emit(mouse->fd, EV_KEY, KEY_ENTER, state);
}

MOUSE_COORD_FUN(moveMouse) {
    emit(mouse->fd, EV_REL, REL_X, x);
    emit(mouse->fd, EV_REL, REL_Y, y);
}

MOUSE_COORD_FUN(scrollMouse) {
    emit(mouse->fd, EV_REL, REL_WHEEL, y);
    emit(mouse->fd, EV_REL, REL_HWHEEL, x);
}