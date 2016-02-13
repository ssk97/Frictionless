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
    Uint8 left_btn, right_btn, up_btn;
    Exhaust myExhaust;
};

class ActivePlayer : public Player
{
    using Player::Player;
};

class OtherPlayer : public Player
{
public:
    OtherPlayer(double x, double y, double angle, IPaddress ip);
    IPaddress ipAddr;
};
