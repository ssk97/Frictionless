#pragma once
#include "globals.h"
#include "Exhaust.h"
#include "Bumper.h"
#include <SDL_net.h>
#include <vector>
class Player
{
public:
    Player(double x, double y, double angle);
    ~Player();
    void step(std::vector<Bumper>* bumpers);
    void draw();
    double x, y, xspd, yspd, angle, aspd;
    Uint8 left_btn, right_btn, up_btn;
    Exhaust myExhaust;
    int colorRed;

};

class ActivePlayer : public Player
{
public:
    using Player::Player;
};

class OtherPlayer : public Player
{
public:
    OtherPlayer(double x, double y, double angle, IPaddress ip);
    IPaddress ipAddr;
};
