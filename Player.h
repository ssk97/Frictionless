#pragma once
#include "globals.h"
class Player
{
public:
	Player(double x, double y, double angle);
	~Player();
	void step();
	void draw();
	double x, y, xspd, yspd, angle, aspd;
private:
	const Uint8 *keyboard;
};

