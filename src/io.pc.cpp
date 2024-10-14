/*
 * FOK-GYEM Tetris Native - PC platform specific IO handling module
 * Copyright (C) 2024 zsotroav
 */

#include <iostream>
#include "config.h"
#include "econio.h"
#include "field.h"
#include "io.h"


void init_io() {
    econio_clrscr();
    econio_rawmode();
}

void print(const field& f) {
    econio_clrscr();

    unsigned char baked[SCREEN_COL_CNT][SCREEN_ROW_CNT] = {0};
    bake(baked, f);

    for (int x = 0; x < SCREEN_ROW_CNT; x++) {
        std::cout << "|";
        for (int y = 0; y < SCREEN_COL_CNT; y++) {
            std::cout << (baked[y][x] == 0 ? " " : "X");
        }
        std::cout << "|" << std::endl;
    }
}

void printMainScreen() {
    econio_clrscr();
    econio_gotoxy(0, 0);
    std::cout << "FOK-GYEM Tetris" << std::endl
              << " PC Compatible " << std::endl
              << "    version    " << std::endl
	          << std::endl
              << " Press any key " << std::endl
              << "   to start.   " << std::endl;
}

void printGameOver(const int score) {
    econio_clrscr();
    econio_gotoxy(0, 0);
    std::cout << "FOK-GYEM Tetris" << std::endl
              << " PC Compatible " << std::endl
              << "    version    " << std::endl
              << std::endl
              << "   GAME OVER   " << std::endl
              << std::endl
              << "   SCORE: " << score << std::endl;
}

bool inputHandle::inputAvailable() {
    if (econio_kbhit()) return true;

    sleep(0.2);
    return false;
}

Control inputHandle::getInput() {
    const int key = econio_getch();
    Control ctrls[] = {CTRL_HARD_DROP, CTRL_SOFT_DROP, CTRL_MOV_R, 
                       CTRL_MOV_L, CTRL_ROT_R, CTRL_ROT_L, CTRL_HOLD};

    // Is this necessary? Eh, I'd rather not return an invalid value
    for (const auto a : ctrls) if (key == a) return a;

    return CTRL_INV;
}
