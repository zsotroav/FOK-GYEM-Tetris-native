
#ifndef NONARDUINO
#include <arduino.h>

void initRand() { randomSeed(analogRead(0)); }

void initRand(unsigned long seed) { randomSeed(seed); }

int getRand(int max) { return random(0, max+1); }

#else
#include <cstdlib>
#include <experimental/random>
#include <ctime>

void initRand() { std::srand(std::time(nullptr)); }

void initRand(unsigned long seed) { std::srand(seed); }

int getRand(int max) { return std::experimental::randint(0, max); }


#endif

