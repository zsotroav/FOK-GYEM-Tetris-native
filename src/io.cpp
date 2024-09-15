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

    buff[6] = 0x55;
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

    // Field base data
    for (int i = 0; i < SCREEN_ROW_CNT; ++i) {
        for (int j = 0; j < SCREEN_COL_CNT; ++j) {
            std::cout << ((f.map[i][j] > 0) ? "X" : " ");
        }
        std::cout << std::endl;
    }

    // Current tetrimino
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            econio_gotoxy(f.current.getX()+j, f.current.getY()+i);
            if (f.current.get(j, i) == 0) continue;
            std::cout << "Z";
        }
    }
    
}

#else

uint8_t buff[DRV_DATABUFF_SIZE] = {0};

void print(const field& f) {
    memset(buff, 0, DRV_DATABUFF_SIZE);

    // Field base data
    for (size_t i = 0; i < DRV_DATABUFF_SIZE; ++i) {
        for (size_t j = 0; j < 8; j++) {
            buff[i] = buff[i] << 1;
            buff[i] |= (f.map[i/3][ (i%3)*8 +j] == 1);
        }
    }

    // Current tetrimino
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (f.current.get(j, i) == 0) continue;

            // econio_gotoxy(f.current.getX()+j, f.current.getY()+i);
            uint8_t d = (0x01 << ((f.current.getY()+i)%8));

            buff[ 3*(f.current.getX()+j) + 3-(f.current.getY()+i)/8 ] = d;
        }
    }

    driver_setBuffer(buff, DRV_DATABUFF_SIZE);
    driver_writeScreen();
}

int arduinoGetInput() {
    // TODO: Ardunino input
    return 999;
}

#endif