//
// Created by zsotroav on 2024-08-22.
//

#include "tetromino.h"

#include "field.h"

bool Tetromino::mov(const bool right, const field& f) {
    if (typ == NONE) return false;
    const int end = x + (right ? 1 : -1);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (get(i, j) == 0) continue;
            if (f.map[this->getY()+j][end+i] != 0) return false;
        }
    }
    x = end;
    return true;
}

bool Tetromino::rotate(const bool right, const field& f) {
    if (typ == NONE) return false;

    const auto next = (right ? rot++ : rot--);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (get(i, j, next) == 0) continue;
            if (f.map[this->getY()+j][this->getX()+i] != 0) return false;
        }
    }

    rot = next;
    return true;
}

bool Tetromino::fall(const field& f) {
    if (typ == NONE) return false;
    const int end = y + 1;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (get(i, j) == 0) continue;
            if (f.map[end+j][x+i] != 0) return false;
        }
    }

    y = end;
    return true;
}

