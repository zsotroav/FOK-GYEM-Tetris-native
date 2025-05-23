//
// Created by zsotroav on 2024-08-20.
//

#ifndef CONFIG_H
#define CONFIG_H

////////////////////////////////////
// Display settings IN PORTRAIT MODE

// Column count of display
#define SCREEN_COL_CNT 7
// Row count of full display
#define SCREEN_ROW_CNT 24
// Screen number of safe rows the player can use to play
#define SCREEN_SAFE_ROW 20
// First row that the player can use
#define SCREEN_PLAY_ROW (SCREEN_ROW_CNT - SCREEN_SAFE_ROW)

///////////////////////////////////////
// Gameplay - spawn point of tetrominos

// Horizontal tetromino spawn point
#define SPAWN_X 4
// Vertical tetromino spawn point
#define SPAWN_Y 6

// Horizontal held position
#define HOLD_X 6
// Vertical held position
#define HOLD_Y 2

// Horizontal position of next tetromino
#define NEXT_X 2
// Vertical position of next tetromino
#define NEXT_Y 2

//////////////////////////////////////////////
// Difficulty settings (tetromino fall speeds)

// Base speed (ms/fall) of tetromino
#define SPD_BASE 800
// Speed increase multiplier
#define SPD_CURVE 202
// Speed increases every x levels
#define LVL_CURVE 10
// Final speed level
#define ULTIMATE_SPD 100

// First starting score (HOLD)
#define START_A_SPD 50
// First starting garbage lines
#define START_A_GAR 3

// First starting score (SDROP)
#define START_B_SPD 80
// First starting garbage lines
#define START_B_GAR 5

// First starting score (HDROP)
#define START_C_SPD 100
// First starting garbage lines
#define START_C_GAR 7

/////////////////////////
// Input Control settings

#ifdef NONARDUINO

#include "econio.h"

typedef enum Control {
    CTRL_HARD_DROP = 'w',
    CTRL_SOFT_DROP = 's',
    CTRL_MOV_R = 'd',
    CTRL_MOV_L = 'a',
    CTRL_ROT_R = KEY_RIGHT,
    CTRL_ROT_L = KEY_LEFT,
    CTRL_HOLD = KEY_UP,
    CTRL_INV  = KEY_UNKNOWNKEY,
} Control;

#else

#include "Arduino.h"

typedef enum Control {
    CTRL_HARD_DROP = A4,
    CTRL_SOFT_DROP = A2,
    CTRL_MOV_R = A1,
    CTRL_MOV_L = A3,
    CTRL_ROT_R = A5,
    CTRL_ROT_L = 1,
    CTRL_HOLD  = 0,
    CTRL_INV   = -1,
} Control;

#endif //NONARDUINO

#endif // CONFIG_H
