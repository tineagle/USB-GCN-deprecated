#include "event.h"

#include <stdio.h>
#include <string.h>

#include "linux/uinput.h"

int main(void) {
    size_t id1 = addController(1);
    if(id1 == SIZE_MAX) {
        return 1;
    }

    while(1) {
        pollEvents();
        ControllerState* state1 = getState(id1);
        // doStuff
    }

    removeController(id1);
}