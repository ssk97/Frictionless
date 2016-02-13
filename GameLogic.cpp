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
	player.input(keyboard[SDL_SCANCODE_RIGHT], keyboard[SDL_SCANCODE_LEFT], keyboard[SDL_SCANCODE_UP]);
	player.step();
	rings.step(player.x, player.y);
	SDL_LockMutex(write_other_players);
	for(auto &p : others)
	{
	    p.step();
	}
	SDL_UnlockMutex(write_other_players);
	send_packet(&player);
}

void GameLogic::draw()
{
	//Clear screen
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	player.draw();
	for(auto &p : others)
	{
	    p.draw();
	}	
	rings.draw();
	//if (other != NULL) other->draw();
}

void GameLogic::addOtherPlayer(double x, double y, double angle, IPaddress ip)
{
    others.push_back(OtherPlayer(x, y, angle, ip));
}
