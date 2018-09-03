#include "event.h"

int main() {
    size_t id1 = addController(1);

    while(1) {
        pollEvents();

        ControllerState* state1 = getState(id1);
        // doStuff
    }

    removeController(id1);
}