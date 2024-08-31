#include <iostream>

#include "common.h"
#include "display.h"
#include "econio.h"
#include "tetrimino.h"

field f;

void setup() {
    init();
    f.prevFrame = millis();

}

int it = 0;

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
        case 'w': /* hard drop */
        case 's': /* soft drop */ break;
        case 'a': f.mov(false); break;
        case 'd':  f.mov(true); break;
        case KEY_LEFT: f.rot(false);  break;
        case KEY_RIGHT: f.rot(true);  break;
        case KEY_UP: /* store */
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