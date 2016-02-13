#pragma once
#include "globals.h"
#include "Player.h"
struct Ring {
	double x, y;
};
class RingMaster
{
public:
	RingMaster();
	~RingMaster();
	void step();
	void draw();
	Ring rings[20];
};
