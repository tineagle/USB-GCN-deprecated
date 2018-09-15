#include "event.h"

#include "usb.h"
#include <memory.h>
#include <stdio.h>

USBDevice* devices[4];
ControllerState controllers[4];

#define UPDATE_MATH(OLD, CURRENT) ((uint8_t) OLD << 1) | (uint8_t) CURRENT
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

ControllerState* pollEvents(int id) {
    GameCube currentState;
    USBDevice* device = devices[id];

    freopen(device->path, "r", device->file);
    fread(&currentState, sizeof(GameCube), 1, device->file);

    updateTransitions(controllers + id, &currentState);
    controllers[id].rawState = currentState;
    return controllers + id;
}

size_t getIndex(size_t controllerID) {
    return controllerID % 4;
}

ControllerState* getState(size_t controllerID) {
    size_t index = getIndex(controllerID);

    return devices[index] == NULL ? NULL : controllers + index;
}

size_t addController(size_t controllerID, char* name) {
    size_t index = getIndex(controllerID);

    if(devices[index] != NULL) {
        return SIZE_MAX;
    }

    char* devIDs[] = {"1", "2", "3", "4"};
    devices[index] = openDevice(name);
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