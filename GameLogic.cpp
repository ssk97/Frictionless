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

    if (multiplayer && turns == 10)
    {
        send_packet(&player);
        turns = 0;
    }
    turns++;
}

void GameLogic::draw()
{
    //Clear screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
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
