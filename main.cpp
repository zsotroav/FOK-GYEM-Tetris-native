#include <iostream>

#include "display.h"
#include "tetrimino.h"


void setup() {
    init();

    field f;

    f.current = Tetrimino(L);
    f.map[5][4] = 1;

    print(f);

    f.current.mov(true, f);
    print(f);
    f.current.fall(f);
    print(f);
    f.current.fall(f);
    print(f);
    f.current.mov(true, f);
    print(f);
    f.current.mov(true, f);
    print(f);

    std::cout << "asd" << std::endl << std::flush;
}

void loop() {

}

// if not running on arduino
int main() {
    setup();
    //while(true) loop();
}