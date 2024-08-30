//
// Created by zsotroav on 2024-08-21.
//

#ifndef FIELD_H
#define FIELD_H

#include "config.h"
#include "tetrimino.h"

class field {    
    /**
     * Merge current tetrimino onto the final map
     * @returns success notice
     */
    bool merge();

public:
    unsigned char map[SCREEN_ROW_CNT][SCREEN_COL_CNT]{0};

    Tetrimino current; //!< Current (moving tetrimino)
    Tetrimino next;
    Tetrimino hold;

    field() : current(NONE), next(NONE), hold(NONE) {}

    /**
     * Finish current tetrimino's movement and set up the next
     * @retruns success notice
     */
    bool finishMove();
};



#endif //FIELD_H
