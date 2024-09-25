#include "io.h"
#include "config.h"

void bake(unsigned char baked[SCREEN_COL_CNT][SCREEN_ROW_CNT], const field& f) {
    // Field base data
    for (int x = 1; x <= SCREEN_COL_CNT; x++) {
        for (int y = 1; y <= SCREEN_ROW_CNT; y++) {
            if (f.map[y][x] == 0) continue;
            baked[x-1][y-1] = 1;
        }
    }
    
    // Current tetrimino
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (f.current.get(j, i) == 0) continue;
            
            baked[j + f.current.getX()-1][i + f.current.getY()-1] = 1;
        }
    }

    // Next and held tetrimino
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            baked[j][i]   |= f.next.getStored(j, i, true);
            baked[j+3][i] |= f.hold.getStored(j, i, false);
        }        
    }
}