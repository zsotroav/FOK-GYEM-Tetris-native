/*
 * FOK-GYEM Tetris Native
 * Arduino platform specific implementations of common functions
 * Copyright (C) 2024 zsotroav
 */

#ifdef NONARDUINO
#include <cstdlib>
#include <experimental/random>
#include <ctime>
#include "common.h"
#include "econio.h"


void initRand() { std::srand(std::time(nullptr)); }

void initRand(const unsigned long seed) { std::srand(seed); }

int getRand(const int max) { return std::experimental::randint(0, max); }


unsigned long time() {
    timespec t {} ;
    #ifdef WIN32
        clock_gettime ( CLOCK_MONOTONIC , & t ) ;
    #else
        clock_gettime ( CLOCK_MONOTONIC_RAW , & t ) ;
    #endif
    return t.tv_sec * 1000 + ( t.tv_nsec + 500000 ) / 1000000 ;
}

void sleep(const double sec) { econio_sleep(sec); }

#endif

