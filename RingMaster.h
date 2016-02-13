#pragma once
#include "globals.h"
#include "Player.h"

#define RING_MAX 20
struct Ring {
    double x, y;
    int status;//-60 = invisible, -59 to -1 = growing, 0 = waiting, 1 to 60 = disappearing
};
class RingMaster
{
public:
    RingMaster();
    ~RingMaster();
    void step(double x, double y);
    void draw();
    void init();
    Ring rings[RING_MAX];
    int thisRing = 0;
};
