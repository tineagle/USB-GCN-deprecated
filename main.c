#define _GNU_SOURCE

#include "event.h"
#include "mouse.h"

#include <stdio.h>
#include <string.h>

#include "linux/uinput.h"

#include <unistd.h>

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
        forwardClick(mouse, 0);
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

    if(state->Start == RISING) {
        enterKey(mouse, 1);
    } else if(state->Start == FALLING) {
        enterKey(mouse, 0);
    }

    if(state->Y == RISING) {
        ctrlKey(mouse, 1);
        shiftKey(mouse, 1);
        tabKey(mouse, 1);
    } else if(state->Y == FALLING) {
        tabKey(mouse, 0);
        shiftKey(mouse, 0);
        ctrlKey(mouse, 0);
    }

    if(state->X == RISING) {
        ctrlKey(mouse, 1);
        tabKey(mouse, 1);
    } else if(state->X == FALLING) {
        tabKey(mouse, 0);
        ctrlKey(mouse, 0);
    }

    if(state->Z == RISING) {
        altKey(mouse, 1);
    } else if(state->Z == FALLING) {
        altKey(mouse, 0);
    }

    int dxMouse;
    if(state->rawState.mainStick.LR > 160) dxMouse =  15;
    else if(state->rawState.mainStick.LR <= 90) dxMouse = -15;
    else dxMouse = 0;
    int dyMouse;
    if(state->rawState.mainStick.UD > 160) dyMouse =  15;
    else if(state->rawState.mainStick.UD <= 90) dyMouse = -15;
    else dyMouse = 0;

    moveMouse(mouse, dxMouse, dyMouse);

    int dxScroll;
    if(state->rawState.cStick.LR > 160) dxScroll =  2;
    else if(state->rawState.cStick.LR <= 90) dxScroll = -2;
    else dxScroll = 0;
    int dyScroll;
    if(state->rawState.cStick.UD > 160) dyScroll =  -2;
    else if(state->rawState.cStick.UD <= 90) dyScroll = 2;
    else dyScroll = 0;
    scrollMouse(mouse, dxScroll, dyScroll);

    sendEvents(mouse);
}

#include <unistd.h>
#include <time.h>

int main(void) {
    size_t id0 = addController(1);
    Mouse* mouse = createMouse();
    if(id0 == SIZE_MAX) {
        return 1;
    }

    struct timespec start;
    struct timespec end;
    struct timespec request;
    struct timespec remaining;
    int i = 0;
    while(1) {
        clock_gettime(CLOCK_REALTIME, &start);
        ControllerState* state = pollEvents(id0);
        handleState(state, mouse);
        clock_gettime(CLOCK_REALTIME, &end);
        long elapse = end.tv_nsec - start.tv_nsec;
        request.tv_nsec = 16500000 - elapse;
        request.tv_sec = 0;
        nanosleep(&request, &remaining);
    }

    removeController(id0);
    destroyMouse(mouse);
}