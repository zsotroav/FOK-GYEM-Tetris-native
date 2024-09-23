//
// Created by zsotroav on 2024-08-20.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include "field.h"

void init_io();

void print(const field& f);

class inputHandle {
    Control prev_input = CTRL_INV;

public:
    bool inputAvailable();
    Control getInput();
};

#endif //DISPLAY_H
