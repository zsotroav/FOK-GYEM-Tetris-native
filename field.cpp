//
// Created by zsotroav on 2024-08-21.
//

#include "field.h"
#include "common.h"

bool field::merge() {
    int x = current.getX(), y = current.getY();

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (current.get(j,i) == 0) continue;
            if (map[y+i][x+j] != 0) return false;
            map[y+i][x+j] = 1;
        }        
    }
    return true;    
}


bool field::finishMove() {
    if (!merge()) return false;

    current = next;
    next = Tetrimino(static_cast<tetriminoType>(getRand()));

    char cleared = 0;

    for (int i = SCREEN_ROW_CNT-1; i > SPAWN_Y; --i) {
        bool ok = true;
        for (int j = 0; j < SCREEN_COL_CNT; ++j) {
            if (map[i][j] == 0) { ok = false; break; }
        }
        if (!ok) continue;

        for (int j = i; j > SCREEN_PLAY_ROW+1; --j) {
            for (int k = 0; k < SCREEN_COL_CNT; ++k) map[j][k] = map[j-1][k];
        }
        cleared++;
        --i;
    }

    if (tetris && cleared == 4) cleared++;
    score += scoreArr[cleared-1];

    for (int i = 0; i < SCREEN_COL_CNT; ++i) {
        if (map[SPAWN_X][i] != 0) return false;
    }

    return true;
}

bool field::fall() {
    if (current.fall(*this)) return true;
    return this->finishMove();
}
