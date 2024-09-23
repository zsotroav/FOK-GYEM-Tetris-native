#ifndef COMMON_H
#define COMMON_H


void initRand();
void initRand(unsigned long seed);

int getRand(int max = 6);

#ifdef NONARDUINO

#include "econio.h"

unsigned long millis();

// Reimplementation of the Arduino delay function using econio
inline void delay(double sec) { econio_sleep(sec); }
#endif

#endif