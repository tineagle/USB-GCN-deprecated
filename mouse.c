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

    ioctl(mouse->fd, UI_DEV_SETUP, &usetup);
    ioctl(mouse->fd, UI_DEV_CREATE);
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

MOUSE_COORD_FUN(moveMouse) {
    emit(mouse->fd, EV_REL, REL_X, x);
    emit(mouse->fd, EV_REL, REL_Y, y);
}

MOUSE_COORD_FUN(scrollMouse) {
    emit(mouse->fd, EV_REL, REL_WHEEL, y);
    emit(mouse->fd, EV_REL, REL_HWHEEL, x);
}