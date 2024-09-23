/*
 * FOK-GYEM Tetris Native - PC platform specific IO handling module
 * Copyright (C) 2024 zsotroav
 */

#ifdef NONARDUINO

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

#endif