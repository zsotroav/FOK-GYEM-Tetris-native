//
// Created by zsotroav on 2024-08-20.
//

#ifndef TETRIMINO_H
#define TETRIMINO_H

#include "common.h"
#include "config.h"

class field;

enum tetriminoRotation {
    ROTA = 0,
    ROTB = 1,
    ROTC = 2,
    ROTD = 3,
};

// Rotate tetrimino right
inline tetriminoRotation operator++(const tetriminoRotation& t, int) {
    switch (t) {
        case ROTA: return ROTB;
        case ROTB: return ROTC;
        case ROTC: return ROTD;
        default:   return ROTA;
    }
}

// Rotate tetrimino left
inline tetriminoRotation operator--(const tetriminoRotation& t, int) {
    switch (t) {
        case ROTA: return ROTD;
        case ROTB: return ROTA;
        case ROTC: return ROTB;
        default:   return ROTC;
    }
}

enum tetriminoType {
    NONE = -1,
    SQUARE = 0,
    I = 1,
    L = 2,
    LMIRROR = 3,
    N = 4,
    NMIRROR = 5,
    T = 6,
};

enum tetriminoState {
    NEXT,
    HOLD,
    PLAY,
};

// type x rot x hori x vert
const unsigned char tetriminos[7][4][5][5] =
{
    { // Square
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        }
    },
    { // I
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 1},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {1, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },
    { // L
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },
    { // J
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
        }
    },
    { // Z
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },
    { // S
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
        }
    },
    { // T
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }
    }
};

const unsigned char tetriminoStored[7][2][3][4] = {
    { // Square
        {
            { 1, 1, 0, 0 },
            { 1, 1, 0, 0 },
            { 0, 0, 0, 0 },
        },
        {
            { 0, 0, 0, 0 },
            { 0, 0, 1, 1 },
            { 0, 0, 1, 1 },
        }
    },
    { // I
        {
            { 1, 1, 1, 1 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
        },
        {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 1, 1, 1, 1 },
        }
    },
    { // L
        {
            { 1, 0, 0, 0 },
            { 1, 0, 0, 0 },
            { 1, 1, 0, 0 },
        },
        {
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 1, 1 },
        }
    },
    { // J
        {
            { 0, 1, 0, 0 },
            { 0, 1, 0, 0 },
            { 1, 1, 0, 0 },
        },
        {
            { 0, 0, 0, 1 },
            { 0, 0, 0, 1 },
            { 0, 0, 1, 1 },
        }
    },
    { // Z
        {
            { 1, 1, 0, 0 },
            { 0, 1, 1, 0 },
            { 0, 0, 0, 0 },
        },
        {
            { 0, 0, 0, 0 },
            { 0, 1, 1, 0 },
            { 0, 0, 1, 1 },
        }
    },
    { // S
        {
            { 0, 1, 1, 0 },
            { 1, 1, 0, 0 },
            { 0, 0, 0, 0 },
        },
        {
            { 0, 0, 0, 0 },
            { 0, 0, 1, 1 },
            { 0, 1, 1, 0 },
        }

    },
    { // T
        {
            { 1, 1, 1, 0 },
            { 0, 1, 0, 0 },
            { 0, 0, 0, 0 },
        },
        {
            { 0, 0, 0, 0 },
            { 0, 1, 1, 1 },
            { 0, 0, 1, 0 },
        }
    }
};

class Tetrimino {
    int x, y;
    tetriminoType typ;
    tetriminoRotation rot;
public:

    int getX() const { return x; }
    int getY() const { return y; }

    tetriminoType getType() const { return typ; }

    void resetLoc(const int x = SPAWN_X, const int y = SPAWN_Y) {
        rot = ROTA;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (get(j, i) != 2) continue;
                this->x = x - j;
                this->y = y - i;
                return;
            }
        }
    }

    explicit Tetrimino(const tetriminoType t, const tetriminoRotation r = ROTA,
                       const int x = SPAWN_X, const int y = SPAWN_Y
                       ) : typ(t), rot(r) {
        if (typ == NONE) {
            this->x = 0;
            this->y = 0;
            return;
        }

        resetLoc(x, y);
    }

    explicit Tetrimino(const tetriminoType t, const tetriminoState s,
                       const tetriminoRotation r = ROTA) : typ(t), rot(r) {
        if (typ == NONE) {
            this->x = 0;
            this->y = 0;
            return;
        }

        resetLoc();
    }

    Tetrimino() : Tetrimino(static_cast<tetriminoType>(getRand())) {}

    explicit Tetrimino(const tetriminoState s) :
        Tetrimino(static_cast<tetriminoType>(getRand()), s) {}

    unsigned char get(const int x, const int y, const tetriminoRotation r) const {
        if (typ == NONE) return 0;
        return tetriminos[typ][r][y][x];
    }

    unsigned char getStored(const int x, const int y, const bool next) const {
        if (typ == NONE) return 0;
        return tetriminoStored[typ][next ? 0 : 1][y][x];
    }

    unsigned char get(const int x, const int y) const { return get(x, y, rot); }

    // Probably not the best that the tetrimino is asking for the field, but ehh
    bool rotate(bool right, const field& f);

    bool mov(bool right, const field& f);
    bool fall(const field& f);
};

#endif //TETRIMINO_H
