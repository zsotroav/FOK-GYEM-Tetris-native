
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

void initRand(const unsigned long seed) { std::srand(seed); }

int getRand(const int max) { return std::experimental::randint(0, max); }


unsigned long millis() {
    timespec t {} ;
    #ifdef WIN32
        clock_gettime ( CLOCK_MONOTONIC , & t ) ;
    #else
        clock_gettime ( CLOCK_MONOTONIC_RAW , & t ) ;
    #endif
    return t.tv_sec * 1000 + ( t.tv_nsec + 500000 ) / 1000000 ;
}


#endif

