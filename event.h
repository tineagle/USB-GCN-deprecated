#ifndef EVENT_H
#define EVENT_H

#include "gcn.h"
#include <stddef.h>

typedef enum ButtonTransition {
    LOW     = 0,
    RISING  = 1,
    FALLING = 2,
    HIGH    = 3,
} eButtonTransition;

typedef struct ControllerState {
    GameCube rawState;

    eButtonTransition A: 2;
    eButtonTransition B: 2;
    eButtonTransition X: 2;
    eButtonTransition Y: 2;
    eButtonTransition L: 2;
    eButtonTransition R: 2;
    eButtonTransition Z: 2;

    eButtonTransition Start : 2;
    eButtonTransition DUp   : 2;
    eButtonTransition DRight: 2;
    eButtonTransition DDown : 2;
    eButtonTransition DLeft : 2;
} ControllerState;


void pollEvents();
ControllerState* getState(size_t controllerID);

size_t addController(size_t controllerID);
void removeController(size_t controllerID);

#endif