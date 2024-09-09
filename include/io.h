//
// Created by zsotroav on 2024-08-20.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include "field.h"

void init_io();

void print(const field& f);

#ifndef NONARDUINO 

// Reimplementation of the econio getinput for multi-platform functionality
int arduinoGetInput();

#else

// Reimplementation of the Arduino delay function using econio
void delay(double sec) { econio_sleep(sec); }

#endif

#endif //DISPLAY_H
