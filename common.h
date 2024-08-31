#ifndef COMMON_H
#define COMMON_H


void initRand();
void initRand(unsigned long seed);

int getRand(int max = 6);

#ifdef NONARDUINO
unsigned long millis();
#endif

#endif