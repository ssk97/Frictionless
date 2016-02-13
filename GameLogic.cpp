#include "GameLogic.h"
GameLogic::GameLogic() : player(100, 100, 0)
{
    //player = Player(100, 100, 0);
    //Player other = NULL;
}

GameLogic::~GameLogic()
{
}
void GameLogic::step(const Uint8 *keyboard)
{
    player.right_btn = keyboard[SDL_SCANCODE_RIGHT];
    player.left_btn = keyboard[SDL_SCANCODE_LEFT];
    player.up_btn = keyboard[SDL_SCANCODE_UP];
    player.step();
    rings.step(player.x, player.y);
    SDL_LockMutex(write_other_players);
    for(auto &p : others)
    {
        p.step();
    }
    SDL_UnlockMutex(write_other_players);

    if (multiplayer && turns == 3)
    {
        send_packet(&player);
        turns = 0;
    }
    turns++;
    if (rings.thisRing < 20)
        timeFlying++;
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
    rings.draw();
    //if (other != NULL) other->draw();
}

void GameLogic::addOtherPlayer(double x, double y, double angle, IPaddress ip)
{
    multiplayer = 1;
    others.push_back(OtherPlayer(x, y, angle, ip));
}
