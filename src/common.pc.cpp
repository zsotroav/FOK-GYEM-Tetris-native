/*
 * FOK-GYEM Tetris Native
 * Arduino platform specific implementations of common functions
 * Copyright (C) 2024 zsotroav
 */

#include <cstdlib>
#include <ctime>
#include <random>
#include "common.h"
#include "econio.h"


std::mt19937 rng;

void initRand() {
    std::random_device dev;
    rng = std::mt19937(dev());
}

int getRand(const int max) {
    return std::uniform_int_distribution(0, max)(rng);
}


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

