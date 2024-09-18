//
// Created by zsotroav on 2024-08-21.
//

#ifndef FIELD_H
#define FIELD_H

#include "math.h"
#include "config.h"
#include "tetrimino.h"

const short scoreArr[] = {0, 1, 3, 5, 8, 12 };

class field {    
    /**
     * Merge current tetrimino onto the final map
     * @returns success notice
     */
    bool merge();

    bool tetris = false;

    bool canSwap = true;
    bool valid = true;

public:
    unsigned char map[SCREEN_ROW_CNT+2][SCREEN_COL_CNT+2]{0};

    Tetrimino current; //!< Current (moving tetrimino)
    Tetrimino next;
    Tetrimino hold = Tetrimino(NONE);

    int score = 0;
    unsigned int getSpeed() const { return SPD_BASE - sqrt(score/LVL_CURVE) * SPD_CURVE; }

    unsigned long prevFrame = 0;

    bool isValid() { return valid; }

    bool fall();
    bool mov(bool right) { return current.mov(right, *this); }
    bool rot(bool right) { return current.rotate(right, *this); }

    void swap();

    /**
     * Finish current tetrimino's movement and set up the next
     * @retruns success notice
     */
    bool finishMove();

    field() {
        for (int i = 0; i < SCREEN_COL_CNT+2; i++) {
            map[0][i] = 1;
            map[SCREEN_PLAY_ROW][i] = 1;
            map[SCREEN_ROW_CNT+1][i] = 1;
        }
        for (int i = 0; i < SCREEN_ROW_CNT+2; i++) {
            map[i][0] = 1;
            map[i][SCREEN_COL_CNT+1] = 1;
        }
        
    }
};



#endif //FIELD_H
