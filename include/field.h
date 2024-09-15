//
// Created by zsotroav on 2024-08-21.
//

#ifndef FIELD_H
#define FIELD_H

#include "config.h"
#include "tetrimino.h"

const short scoreArr[] = {1, 3, 5, 8, 12 };

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
    unsigned short map[SCREEN_ROW_CNT][SCREEN_COL_CNT]{0};

    Tetrimino current; //!< Current (moving tetrimino)
    Tetrimino next;
    Tetrimino hold = Tetrimino(NONE);

    int score = 0;
    unsigned int getSpeed() const { return SPD_BASE - (score/LVL_CURVE) * SPD_CURVE; }

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
};



#endif //FIELD_H
