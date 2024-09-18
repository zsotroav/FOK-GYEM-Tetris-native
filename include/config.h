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
// Gameplay - spawn point of tetriminos

// Horizontal tetrimino spawn point
#define SPAWN_X 4
// Vertical tetrimino spawn point
#define SPAWN_Y 6

//////////////////////////////////////////////
// Difficulty settings (tetrimino fall speeds)

// Base speed (ms/fall) of tetrimino
#define SPD_BASE 800
// Speed increase (ms/lvl) of tetrimino
#define SPD_CURVE 130
// Speed increases every x levels
#define LVL_CURVE 10

/////////////////////////
// Input Control settings

#ifdef NONARDUINO

#define CTRL_HARD_DROP 'w'
#define CTRL_SOFT_DROP 's'
#define CTRL_MOV_R 'd'
#define CTRL_MOV_L 'a'
#define CTRL_ROT_R KEY_LEFT
#define CTRL_ROT_L KEY_RIGHT
#define CTRL_HOLD KEY_UP

#else //TODO: Actual layout

#include "Arduino.h"

static uint8_t CTRLS[] = {0, 1, A1, A2, A3, A4, A5};

#define CTRL_HARD_DROP A4
#define CTRL_SOFT_DROP A2
#define CTRL_MOV_R A1
#define CTRL_MOV_L A3
#define CTRL_ROT_R A5
#define CTRL_ROT_L 1
#define CTRL_HOLD 0

#endif //NONARDUINO

#endif // CONFIG_H
