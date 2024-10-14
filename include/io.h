//
// Created by zsotroav on 2024-08-20.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include "field.h"

void init_io();

void bake(unsigned char baked[SCREEN_COL_CNT][SCREEN_ROW_CNT], const field& f);

void print(const field& f);

void printMainScreen();

void printGameOver(int score);

class inputHandle {
    Control prev_input;

public:
    bool inputAvailable();
    Control getInput();

    inputHandle() : prev_input(CTRL_INV) {}
};

#endif //DISPLAY_H
