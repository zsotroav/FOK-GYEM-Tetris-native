//
// Created by zsotroav on 2024-08-20.
//

#include "io.h"
#include "field.h"
#include "config.h"

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

    for (auto pin : CTRLS) pinMode(pin, INPUT_PULLUP);

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

void bake(uint8_t baked[SCREEN_COL_CNT][SCREEN_ROW_CNT], const field& f) {
    for (size_t x = 0; x < SCREEN_COL_CNT; x++) {
        for (size_t y = 0; y < SCREEN_ROW_CNT; y++) {
            if (f.map[y][x] == 0) continue;
            baked[x][y] = 1;
        }
    }
    
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (f.current.get(j, i) == 0) continue;
            baked[j + f.current.getX()][i + f.current.getY()] = 1;
        }
    }
}

void print(const field& f) {
    memset(buff, 0, DRV_DATABUFF_SIZE);

    uint8_t baked[SCREEN_COL_CNT][SCREEN_ROW_CNT] = {0};
    bake(baked, f);

    for (size_t x = 0; x < SCREEN_COL_CNT; x++) {
        for (size_t y = 0; y < SCREEN_ROW_CNT; y++) {
            if (baked[x][y] == 0) continue;
        
            const int b = (x+1) * SCREEN_ROW_CNT - y - 1;
            buff[b/8] |= (0x80 >> b%8);
        }
    }

    driver_setBuffer(buff, DRV_DATABUFF_SIZE);
    driver_writeScreen();
}

uint8_t arduinoGetInput() {

    for (auto a : CTRLS) {
        if (digitalRead(a) == LOW) return a;
    }

    return 0xFF;
}

#endif