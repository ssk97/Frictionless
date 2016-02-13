#pragma once
#include "globals.h"
#include "Player.h"
#include "RingMaster.h"
class GameLogic
{
public:
	GameLogic();
	~GameLogic();
	void step(const Uint8*);
	void draw();
	Player player;
	RingMaster rings;
	//Player other;
};
