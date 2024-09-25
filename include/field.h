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

    bool tetris = false; //!< Previous move was a tetris

    bool canSwap = true; //!< Previous move wasn't a swap
    bool valid = true;   //!< Game is in a valid and playable state

    unsigned long prevFrame = time();
    
    int score = 0;

public:
    unsigned char map[SCREEN_ROW_CNT+2][SCREEN_COL_CNT+2]{0};

    Tetrimino current; //!< Current (moving tetrimino)
    Tetrimino next = Tetrimino(NEXT);
    Tetrimino hold = Tetrimino(NONE);

    unsigned int getSpeed() const;
    int getScore() const { return score; }
    bool isValid() const { return valid; }

    bool fall();
    bool mov(const bool right) { return current.mov(right, *this); }
    bool rot(const bool right) { return current.rotate(right, *this); }

    void swap();

    /**
     * Finish current tetrimino's movement and set up the next
     * @retruns success notice
     */
    bool finishMove();

    /**
     * Tick (increment the field timer) and fall automatically when needed
     */
    void tick();

    field() {
        // Fill in map borders
        for (int i = 0; i < SCREEN_COL_CNT+2; i++) {
            map[0][i] = 1; // Fill top border
            map[SCREEN_PLAY_ROW][i] = 1;  // Fill separator row
            map[SCREEN_ROW_CNT+1][i] = 1; // Fill bottom border
        }
        for (int i = 0; i < SCREEN_ROW_CNT+2; i++) {
            map[i][0] = 1; // Fill left border
            map[i][SCREEN_COL_CNT+1] = 1; // Fill right border
        }
        
    }
};



#endif //FIELD_H
