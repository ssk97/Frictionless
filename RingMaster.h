#pragma once
#include "globals.h"
#include "Player.h"

#define RING_MAX 20
struct Ring {
	double x, y;
};
class RingMaster
{
public:
	RingMaster();
	~RingMaster();
	void step(double x, double y);
	void draw();
	Ring rings[RING_MAX];
	int thisRing = 0;
};
