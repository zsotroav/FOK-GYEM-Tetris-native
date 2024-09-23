/*
 * FOK-GYEM Tetris Native - Arduino platform specific IO handling module
 * Copyright (C) 2024 zsotroav
 */

#include <arduino.h>
#include "config.h"
#include "driver.h"
#include "field.h"
#include "io.h"


static Control ctrls[] = {CTRL_HARD_DROP, CTRL_SOFT_DROP, CTRL_MOV_R, 
                       CTRL_MOV_L, CTRL_ROT_R, CTRL_ROT_L, CTRL_HOLD};

void init_io() {

    // Initialize driver
    driver_init();

    // Set buffer and empty the display
    uint8_t buff[DRV_DATABUFF_SIZE] = {0};
    driver_setBuffer(buff, DRV_DATABUFF_SIZE);
    driver_forceWriteScreen();

    buff[6] = 0x55;
    driver_setBuffer(buff, DRV_DATABUFF_SIZE);
    driver_forceWriteScreen();


    for (auto pin : ctrls) pinMode(pin, INPUT_PULLUP);
}

uint8_t buff[DRV_DATABUFF_SIZE] = {0};

void bake(uint8_t baked[SCREEN_COL_CNT][SCREEN_ROW_CNT], const field& f) {
    // Field base data
    for (int x = 1; x <= SCREEN_COL_CNT; x++) {
        for (int y = 1; y <= SCREEN_ROW_CNT; y++) {
            if (f.map[y][x] == 0) continue;
            baked[x-1][y-1] = 1;
        }
    }
    
    // Tetrimino layers
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            // Current tetrimino
            if (f.current.get(j, i) != 0) 
                baked[j + f.current.getX()-1][i + f.current.getY()-1] = 1;

            // Next tetrimino
            if (f.next.get(j, i) != 0) 
                baked[j + f.next.getX()-1][i + f.next.getY()-1] = 1;

            // Held tetrimino
            if (f.hold.get(j, i) != 0) 
                baked[j + f.hold.getX()-1][i + f.hold.getY()-1] = 1;
        }
    }
}

void print(const field& f) {
    memset(buff, 0, DRV_DATABUFF_SIZE);

    uint8_t baked[SCREEN_COL_CNT][SCREEN_ROW_CNT] = {0};
    bake(baked, f);

    for (int x = 0; x < SCREEN_COL_CNT; x++) {
        for (int y = 0; y < SCREEN_ROW_CNT; y++) {
            if (baked[x][y] == 0) continue;
        
            const int b = (x+1) * SCREEN_ROW_CNT - y - 1;
            buff[b/8] |= (0x80 >> b%8);
        }
    }

    driver_setBuffer(buff, DRV_DATABUFF_SIZE);
    driver_writeScreen();
}

Control inputHandle::getInput() {
    for (auto a : ctrls) {
        if (digitalRead(a) == LOW) return a;
    }

    return CTRL_INV;
}

bool inputHandle::inputAvailable() {
    Control curr = getInput();

    bool re = prev_input != curr;
    prev_input = curr;
    return re;
}
