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
    init(); // Init the rest of the Arduino system as well

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

// TODO: Proper dynamic size for this as well?
void printMainScreen() {
    if (DRV_DATABUFF_SIZE != 21) return;

    uint8_t b[] = { 0xFC, 0x00, 0x09, 0xF0, 0x00, 0x0B, 0xE0, 0x10, 0x0A, 0x36,
        0x30, 0x08, 0xEE, 0x10, 0x08, 0xC8, 0x00, 0x08, 0x78, 0x00, 0x08 };
    driver_setBuffer(b, 21);
    driver_forceWriteScreen();
}

void scoreOverlay(uint8_t arr[21], int score) {
    // 2x5 Number font for scoreboard
    uint8_t fnt[10][2] = {
        { B00011111, B00011111 }, // 0
        { B00000000, B00011111 }, // 1
        { B00011101, B00010111 }, // 2
        { B00010101, B00011111 }, // 3
        { B00000111, B00011100 }, // 4
        { B00010111, B00011101 }, // 5
        { B00011111, B00011001 }, // 6
        { B00011001, B00000111 }, // 7
        { B00011011, B00011011 }, // 8
        { B00010011, B00011111 }  // 9
    };

    if (score >= 100) {
        arr[SCREEN_ROW_CNT/8 - 1] |= fnt[1][1];
        score -= 100;
    }

    if (score >= 10) {
        arr[(SCREEN_ROW_CNT*3)/8 - 1] |= fnt[score/10][0];
        arr[(SCREEN_ROW_CNT*4)/8 - 1] |= fnt[score/10][1];
    }

    arr[(SCREEN_ROW_CNT*6)/8 - 1] |= fnt[score%10][0];
    arr[(SCREEN_ROW_CNT*7)/8 - 1] |= fnt[score%10][1];

    /*
    uint32_t off = 0x01;
    for (int i = SCREEN_COL_CNT; i > 0; i--) {
        if ((score & off) != 0) arr[(SCREEN_ROW_CNT * (i) - 1)/8] |= 0x01; 
        off <<= 1;
    }
    */
}

void printGameOver(const int score) {
    if (DRV_DATABUFF_SIZE != 21) {
        uint8_t b[DRV_DATABUFF_SIZE] = {0};
        scoreOverlay(b, score);
        driver_setBuffer(b, DRV_DATABUFF_SIZE);
        driver_writeScreen();
        return;
    }
    
    uint8_t w[] = { 0x64, 0x00, 0x00, 0x52, 0x0F, 0x00, 0x52, 0x10, 0x00, 0x4C,
         0x0E, 0x00, 0x00, 0x90, 0x00, 0x06, 0x8F, 0x00, 0x01, 0x80, 0x00 };

    uint8_t l[] = { 0x00, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x01, 0xFF, 0x00, 0x01, 
        0x80, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00 };

    if (score > 127) {
        scoreOverlay(w, score);
        driver_setBuffer(w, DRV_DATABUFF_SIZE);
    } else {
        scoreOverlay(l, score);
        driver_setBuffer(l, DRV_DATABUFF_SIZE);
    }
    
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
