//
// Created by zsotroav on 2024-08-21.
//

#ifndef FIELD_H
#define FIELD_H

#include "math.h"
#include "config.h"
#include "tetromino.h"

const short scoreArr[] = {0, 10, 30, 50, 80, 120 };

class field {    
    /**
     * Merge current tetromino onto the final map
     * @returns success notice
     */
    bool merge();

    bool tetris = false; //!< Previous move was a tetris

    bool canSwap = true; //!< Previous move wasn't a swap
    bool valid = true;   //!< Game is in a valid and playable state

    unsigned long prevFrame = time();
    
    int score = 0;

    char grace = 1; //!< Number of frames left as a grace period at the end
    void resetGrace() { grace = 1; }

public:
    unsigned char map[SCREEN_ROW_CNT+2][SCREEN_COL_CNT+2]{0};

    Tetromino current; //!< Current (moving tetromino)
    Tetromino next = Tetromino();
    Tetromino hold = Tetromino(NONE);

    unsigned int getSpeed() const;
    int getScore() const { return score; }
    bool isValid() const { return valid; }

    void drop(); //!< Hard drop the tetromino
    bool fall();
    bool mov(const bool right) { return current.mov(right, *this); }
    bool rot(const bool right) { return current.rotate(right, *this); }

    void swap();

    /**
     * Finish current tetromino's movement and set up the next
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
