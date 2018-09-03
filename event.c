#include "event.h"

#include "usb.h"
#include <memory.h>

USBDevice* devices[4];
ControllerState controllers[4];

#define UPDATE_MATH(OLD, CURRENT) (OLD << 1) & CURRENT
#define GET_BUTTON(GC, BUTTON) GC.buttons.BUTTON
#define PGET_BUTTON(GC, BUTTON) GC->buttons.BUTTON
#define UPDATE_TRANSITION(OLD, CURRENT, BUTTON) \
    OLD->BUTTON = UPDATE_MATH(GET_BUTTON(OLD->rawState, BUTTON), PGET_BUTTON(CURRENT, BUTTON))

void updateTransitions(ControllerState* old, GameCube* currentState) {
    UPDATE_TRANSITION(old, currentState, A);
    UPDATE_TRANSITION(old, currentState, B);
    UPDATE_TRANSITION(old, currentState, X);
    UPDATE_TRANSITION(old, currentState, Y);
    UPDATE_TRANSITION(old, currentState, L);
    UPDATE_TRANSITION(old, currentState, R);
    UPDATE_TRANSITION(old, currentState, Z);
    UPDATE_TRANSITION(old, currentState, Start);
    UPDATE_TRANSITION(old, currentState, DUp);
    UPDATE_TRANSITION(old, currentState, DRight);
    UPDATE_TRANSITION(old, currentState, DDown);
    UPDATE_TRANSITION(old, currentState, DLeft);
}

void pollEvents() {
    for(int i = 0; i < 4; ++i) {
        if(devices[i] != NULL) {
            GameCube currentState;
            readLatestData(devices[i], &currentState, sizeof(GameCube));

            updateTransitions(&controllers[i], &currentState);
            controllers[i].rawState = currentState;
        }
    }
}

size_t getIndex(size_t controllerID) {
    return controllerID % 4;
}

ControllerState* getState(size_t controllerID) {
    size_t index = getIndex(controllerID);

    return devices[index] == NULL ? NULL : controllers + index;
}

size_t addController(size_t controllerID) {
    size_t index = getIndex(controllerID);

    if(devices[index] != NULL) {
        return SIZE_MAX;
    }

    char* devIDs[] = {"1", "2", "3", "4"};
    devices[index] = openDevice(devIDs[index]);
    return controllerID;
}

void removeController(size_t controllerID) {
    size_t index = getIndex(controllerID);

    if(devices[index] == NULL) {
        return;
    }

    memset(&controllers[index], 0, sizeof(ControllerState));
    closeDevice(devices[index]);
    devices[index] = NULL;
}