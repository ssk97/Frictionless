#pragma once
#include "globals.h"
#include "Player.h"
#include "RingMaster.h"
#include "network.h"
#include <vector>
class GameLogic
{
public:
	GameLogic();
	~GameLogic();
	void step(const Uint8*);
	void draw();
	void addOtherPlayer(double, double, double, IPaddress);
	ActivePlayer player;
	RingMaster rings;
	std::vector<Player> others;
};
