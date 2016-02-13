#pragma once
#include "globals.h"
#include "Exhaust.h"
#include <SDL_net.h>
class Player
{
public:
	Player(double x, double y, double angle);
	~Player();
	void step();
	void draw();
	double x, y, xspd, yspd, angle, aspd;
	Exhaust myExhaust;
};

class ActivePlayer : public Player
{
    using Player::Player;
public:
	void input(bool right, bool left, bool up);
	Uint8 left_prev, right_prev, up_prev; //It needs to be Uint8 to be sent over the wire.    
};

class OtherPlayer : Player
{
public:
    IPaddress ipAddr;
};
