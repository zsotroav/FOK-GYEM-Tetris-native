#include "common.h"
#include "io.h"


// Gameplay update loop for handling ticks/updates
void gameUpdateLoop(field& f, inputHandle& ih) {
    f.tick();
    print(f);

    if (!ih.inputAvailable()) { return; }

    switch (ih.getInput()) {
        case CTRL_HARD_DROP: f.drop(); break;
        case CTRL_SOFT_DROP: f.fall(); sleep(0.1); break;
        case CTRL_MOV_L: f.mov(false); break;
        case CTRL_MOV_R: f.mov(true);  break;
        case CTRL_ROT_L: f.rot(false); break;
        case CTRL_ROT_R: f.rot(true);  break;
        case CTRL_HOLD:  f.swap();     break;
        default: break;
    }
}

// Gameplay loop creating the field and using it until the game ends
void masterLoop(inputHandle& ih) {
    // Create a new field to play on
    field f;
    
    while(f.isValid()) gameUpdateLoop(f, ih);
    printGameOver(f.getScore()/10);
    sleep(8);
}

int main() {
    init_io();
    initRand();

    inputHandle ih;

    // The game runs indefinitely
    while(true) {
        printMainScreen();
        while (!ih.inputAvailable()) { sleep(0.2); }

        // Consuming input is required for some systems
        ih.getInput(); 
        
        // Enter the master gameplay loop
        masterLoop(ih);
    }
}