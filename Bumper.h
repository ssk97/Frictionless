#pragma once
#include "globals.h"

#define BUMPER_NO_COLLISION 0
#define BUMPER_X_COLLISION 1
#define BUMPER_Y_COLLISION 2

class Bumper
{
public:
    Bumper(double x, double y, double width);
    ~Bumper();
    void draw();
    int calculateCollision(double, double);
    double x, y, width;
};
