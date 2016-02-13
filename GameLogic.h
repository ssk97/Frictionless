#pragma once
#include "globals.h"
#include "Player.h"
class GameLogic
{
public:
	GameLogic();
	~GameLogic();
	void step(const Uint8*);
	void draw();
	Player player;
	//Player other;
};
