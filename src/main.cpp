#ifdef NONARDUINO
#include <iostream>
#else
#include <Arduino.h>
#endif

#include "common.h"
#include "display.h"
#include "econio.h"

field f;

void setup() {
    init_display();
    f.prevFrame = millis();
}

void loop() {
    unsigned long t = millis();
    if (f.prevFrame + f.getSpeed() < t) {
        f.fall();
        f.prevFrame = millis();
    }
    print(f);

#ifdef NONARDUINO
    if (!econio_kbhit()) { econio_sleep(0.2); return; }

    switch (econio_getch()) {
        case 'w': while (f.fall()) {} break;
        case 's': f.fall(); econio_sleep(0.1); break;
        case 'a': f.mov(false); break;
        case 'd':  f.mov(true); break;
        case KEY_LEFT: f.rot(false); break;
        case KEY_RIGHT: f.rot(true); break;
        case KEY_UP: f.swap(); break;
        default: break;
    }
#else
#endif
}

// if not running on arduino
int main() {
    setup();
    while(true) loop();
}