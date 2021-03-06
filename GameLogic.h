#pragma once
#include "globals.h"
#include "Player.h"
#include "Bumper.h"
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
    std::vector<Bumper> bumpers;
    SDL_mutex* write_other_players;
    int multiplayer = 0;
    int turns = 0;
    Uint8 opponent_rings;
    bool haveWon = false;

    int timeFlying = 0;
};
