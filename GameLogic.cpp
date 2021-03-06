#include "GameLogic.h"
GameLogic::GameLogic() : player(100, 100, 0)
{
    //player = Player(100, 100, 0);
    //Player other = NULL;
}

GameLogic::~GameLogic()
{
}
int buttonLast = 0;
void GameLogic::step(const Uint8 *keyboard)
{
    player.right_btn = keyboard[SDL_SCANCODE_RIGHT];
    player.left_btn = keyboard[SDL_SCANCODE_LEFT];
    player.up_btn = keyboard[SDL_SCANCODE_UP];
    player.step(&bumpers);
    SDL_LockMutex(write_other_players);
    for(auto &p : others)
    {
        p.step(&bumpers);
    }
    SDL_UnlockMutex(write_other_players);

    if (keyboard[SDL_SCANCODE_F] && !buttonLast) player.multiplier *= 1.5;
    buttonLast = keyboard[SDL_SCANCODE_F];

    if (multiplayer && turns == 3)
    {
        send_packet(&player, rings.thisRing);
        turns = 0;
    }
    turns++;
    if (rings.thisRing < 20) {
        timeFlying++;
        rings.step(player.x, player.y);
    }
}

void GameLogic::draw()
{

    player.draw();
    SDL_LockMutex(write_other_players);
    for(auto &p : others)
    {
        p.draw();
    }
    SDL_UnlockMutex(write_other_players);
    if (rings.thisRing < 20) {
        rings.draw();
    }
    for (auto &b : bumpers)
    {
	    b.draw();
    }
    if (multiplayer && opponent_rings < 20)
        rings.drawEnemy(opponent_rings);

    //if (other != NULL) other->draw();
}

void GameLogic::addOtherPlayer(double x, double y, double angle, IPaddress ip)
{
    multiplayer = 1;
    others.push_back(OtherPlayer(x, y, angle, ip));
}
