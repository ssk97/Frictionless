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
	/*if (other != NULL)
	{
		other->step();
	}*/
}

void GameLogic::draw()
{
	//Clear screen
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	player.draw();
	//if (other != NULL) other->draw();
}
