#ifdef NONARDUINO
#include <iostream>
#else
#include <Arduino.h>
#endif

#include "common.h"
#include "io.h"
#include "econio.h"

field f;

void setup() {
    init_io();
    f.prevFrame = millis();
}

void loop() {
    unsigned long t = millis();
    if (f.prevFrame + f.getSpeed() < t) {
        f.fall();
        f.prevFrame = t;
    }
    print(f);

#ifdef NONARDUINO
    // TODO: Squash these?
    if (!econio_kbhit()) { delay(0.2); return; }

    switch (econio_getch()) {
#else
    switch (arduinoGetInput()) {
#endif

        case CTRL_HARD_DROP: while (f.fall()) {} break;
        case CTRL_SOFT_DROP: f.fall(); delay(0.1); break;
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