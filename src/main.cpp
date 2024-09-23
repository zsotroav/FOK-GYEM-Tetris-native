#include "common.h"
#include "io.h"

field f;
inputHandle ih;

void setup() {
    init_io();
    initRand();
    f.prevFrame = time();
}

void loop() {
    unsigned long t = time();
    if (f.prevFrame + f.getSpeed() < t) {
        f.fall();
        f.prevFrame = t;
    }
    print(f);

    if (!ih.inputAvailable()) { sleep(0.2); return; }

    switch (ih.getInput()) {
        case CTRL_HARD_DROP: while (f.fall()) {} break;
        case CTRL_SOFT_DROP: f.fall(); sleep(0.1); break;
        case CTRL_MOV_L: f.mov(false); break;
        case CTRL_MOV_R: f.mov(true);  break;
        case CTRL_ROT_L: f.rot(false); break;
        case CTRL_ROT_R: f.rot(true);  break;
        case CTRL_HOLD:  f.swap();     break;
        default: break;
    }
}

// if not running on arduino
#ifdef NONARDUINO
int main() {
    setup();
    while(true) loop();
}
#endif