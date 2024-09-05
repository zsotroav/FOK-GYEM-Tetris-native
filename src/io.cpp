//
// Created by zsotroav on 2024-08-20.
//

#include "io.h"
#include "field.h"

#ifndef NONARDUINO

#include <arduino.h>
#include "driver.h"

#else

#include <iostream>
#include "econio.h"

#endif


void init_io() {

#ifndef NONARDUINO

    // Initialize driver
    driver_init();

    // Set buffer and empty the display
    uint8_t buff[DRV_DATABUFF_SIZE] = {0};
    driver_setBuffer(buff, DRV_DATABUFF_SIZE);
    driver_forceWriteScreen();

    pinMode(CTRL_HARD_DROP, INPUT);
    pinMode(CTRL_SOFT_DROP, INPUT);
    pinMode(CTRL_MOV_R, INPUT);
    pinMode(CTRL_MOV_L, INPUT);
    pinMode(CTRL_ROT_R, INPUT);
    pinMode(CTRL_ROT_L, INPUT);
    pinMode(CTRL_HOLD, INPUT);

#else

    econio_clrscr();
    econio_rawmode();

#endif

}


#ifdef NONARDUINO
void print(const field& f) {
    econio_clrscr();

    for (int i = 0; i < SCREEN_ROW_CNT; ++i) {
        for (int j = 0; j < SCREEN_COL_CNT; ++j) {
            std::cout << ((f.map[i][j] > 0) ? "X" : " ");
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            econio_gotoxy(f.current.getX()+j, f.current.getY()+i);
            if (f.current.get(j, i) == 0) continue;
            std::cout << "Z";
        }
    }
    
}

#else

void print(const field& f) {

}

int arduinoGetInput() {
    return 0;
}

#endif