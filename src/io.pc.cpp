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

    // Field base data
    for (int i = 0; i < SCREEN_ROW_CNT+2; ++i) {
        for (int j = 0; j < SCREEN_COL_CNT+2; ++j) {
            std::cout << ((f.map[i][j] > 0) ? "X" : " ");
        }
        std::cout << std::endl;
    }

    // Current tetrimino
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (f.current.get(j, i) != 0) {
                econio_gotoxy(f.current.getX()+j, f.current.getY()+i);
                std::cout << "Z";
            }
            
            if (f.next.get(j, i) != 0) {
                econio_gotoxy(f.next.getX()+j, f.next.getY()+i);
                std::cout << "Z";
            }
            
            if (f.hold.get(j, i) != 0) {
                econio_gotoxy(f.hold.getX()+j, f.hold.getY()+i);
                std::cout << "Z";
            }
        }
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

bool inputHandle::inputAvailable() { return econio_kbhit(); }

Control inputHandle::getInput() { 
    int key = econio_getch();
    Control ctrls[] = {CTRL_HARD_DROP, CTRL_SOFT_DROP, CTRL_MOV_R, 
                       CTRL_MOV_L, CTRL_ROT_R, CTRL_ROT_L, CTRL_HOLD};

    // Is this necessary? Eh, I'd rather not return an invalid value
    for (auto a : ctrls) if (key == a) return a;

    return CTRL_INV;
}
