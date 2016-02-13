#pragma once
#include "globals.h"
#include "Exhaust.h"
class Player
{
public:
	Player(double x, double y, double angle);
	~Player();
	void step();
	void draw();
	void input(bool right, bool left, bool up);
	struct playerDataToSync getPlayerDataToSync();
	double x, y, xspd, yspd, angle, aspd;
	Uint8 left_prev, right_prev, up_prev; //It needs to be Uint8 to be sent over the wire.
	Exhaust myExhaust;
};
