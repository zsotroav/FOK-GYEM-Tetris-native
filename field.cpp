//
// Created by zsotroav on 2024-08-21.
//

#include "field.h"
#include "common.h"

bool field::merge() {
    int x = current.getX(), y = current.getY();

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (current.get(i,j) == 0) continue;
            if (map[i][j] != 0) return false;
            map[i][j] = 1;
        }        
    }
    return true;    
}


bool field::finishMove() {
    if (!merge()) return false;

    current = next;
    next = Tetrimino(static_cast<tetriminoType>(getRand()));
}