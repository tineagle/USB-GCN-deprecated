#include "event.h"
#include "mouse.h"

#include <stdio.h>
#include <string.h>

#include "linux/uinput.h"

void handleState(ControllerState* state, Mouse* mouse) {
    if(state->A == RISING) {
        leftClick(mouse, 1);
    } else if(state->A == FALLING) {
        leftClick(mouse, 0);
    }

    if(state->B == RISING) {
        rightClick(mouse, 1);
    } else if(state->B == FALLING) {
        rightClick(mouse, 0);
    }

    if(state->L == RISING) {
        backClick(mouse, 1);
    } else if(state->L == FALLING) {
        backClick(mouse, 0);
    }

    if(state->R == RISING) {
        forwardClick(mouse, 1);
    } else if(state->R == FALLING) {
        backClick(mouse, 0);
    }

    if(state->DUp == RISING) {
        upArrow(mouse, 1);
    } else if(state->DUp == FALLING) {
        upArrow(mouse, 0);
    }

    if(state->DRight == RISING) {
        rightArrow(mouse, 1);
    } else if(state->DRight == FALLING) {
        rightArrow(mouse, 0);
    }

    if(state->DDown == RISING) {
        downArrow(mouse, 1);
    } else if(state->DDown == FALLING) {
        downArrow(mouse, 0);
    }

    if(state->DLeft == RISING) {
        leftArrow(mouse, 1);
    } else if(state->DLeft == FALLING) {
        leftArrow(mouse, 0);
    }

    int dxMouse;
    if(state->rawState.mainStick.LR > 20) dxMouse =  5;
    if(state->rawState.mainStick.LR < 20) dxMouse = -5;
    int dyMouse;
    if(state->rawState.mainStick.UD > 20) dyMouse =  5;
    if(state->rawState.mainStick.UD < 20) dyMouse = -5;
    moveMouse(mouse, dxMouse, dyMouse);

    int dxScroll;
    if(state->rawState.cStick.LR > 20) dxScroll =  5;
    if(state->rawState.cStick.LR < 20) dxScroll = -5;
    int dyScroll;
    if(state->rawState.cStick.UD > 20) dyScroll =  5;
    if(state->rawState.cStick.UD < 20) dyScroll = -5;
    scrollMouse(mouse, dxScroll, dyScroll);

    sendEvents(mouse);
}

#include <unistd.h>

int main(void) {
    size_t id1 = addController(0);
    Mouse* mouse = createMouse();

    if(id1 == SIZE_MAX) {
        return 1;
    }

    while(1) {
        pollEvents();
        ControllerState* state1 = getState(id1);
        // doStuff
    }

    removeController(id1);
    destroyMouse(mouse);
}