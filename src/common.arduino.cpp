/*
 * FOK-GYEM Tetris Native
 * Arduino platform specific implementations of common functions
 * Copyright (C) 2024 zsotroav
 */

#ifndef NONARDUINO
#include <arduino.h>
#include "common.h"


void initRand() { randomSeed(analogRead(0)); }

void initRand(unsigned long seed) { randomSeed(seed); }

int getRand(int max) { return random(0, max+1); }

unsigned long time() { return millis(); }

void sleep(double sec) { delay(sec*1000); }

#endif