//
// Created by zsotroav on 2024-08-21.
//

#include "field.h"
#include "common.h"

unsigned int field::getSpeed() const { 
    if (score >= 128) return ULTIMATE_SPD;
    return SPD_BASE - sqrt(score/LVL_CURVE) * SPD_CURVE; 
}

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
    current.resetLoc();
    next = Tetrimino(static_cast<tetriminoType>(getRand()), NEXT);

    int cleared = 0;

    for (int i = SCREEN_ROW_CNT; i > SCREEN_PLAY_ROW; --i) {
        bool ok = true;
        for (int j = 1; j <= SCREEN_COL_CNT; ++j) {
            if (map[i][j] == 0) { ok = false; break; }
        }
        if (!ok) continue;

        for (int j = i; j > SCREEN_PLAY_ROW+1; --j) {
            for (int k = 1; k <= SCREEN_COL_CNT; ++k) map[j][k] = map[j-1][k];
        }
        cleared++;
        ++i; // Go back to check the now shifted down row again
    }

    // Handle back-to-back tetris (4x clear)
    if (tetris && cleared == 4) cleared++;
    tetris = (cleared == 4);

    score += scoreArr[cleared];

    for (int i = 1; i <= SCREEN_COL_CNT; ++i) {
        if (map[SPAWN_X+3][i] == 0) continue;
        valid = false;
        return false;
    }

    canSwap = true;
    return true;
}

bool field::fall() {
    if (current.fall(*this)) return true;
    this->finishMove();
    return false;
}

void field::swap() {
    if (!canSwap) return;
    canSwap = false;
    if (hold.getType() == NONE) {
        hold = next;
        next = Tetrimino(NEXT);
    }

    const auto tmp = hold;
    hold = current;
    current = tmp;
    
    current.resetLoc();
}

void field::tick() {
    unsigned long t = time();
    if (prevFrame + getSpeed() < t) {
        fall();
        prevFrame = t;
    }
}