#ifndef COMMON_H
#define COMMON_H


void initRand();
void initRand(unsigned long seed);

// Get random number [0, max]
int getRand(int max = 6);

// ms since startup
unsigned long time();

// Sleep/Delay the current thread for the given seconds
void sleep(double sec);

#endif