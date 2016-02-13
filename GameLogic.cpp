#include "GameLogic.h"

void gameLogicLoop(Player* player, Player* other, const Uint8 *keyboard)
{
	player->input(keyboard[SDL_SCANCODE_RIGHT], keyboard[SDL_SCANCODE_LEFT], keyboard[SDL_SCANCODE_UP]);
	player->step();
	if (other != NULL)
	{
		other->step();
	}
}

void drawLoop(Player* player, Player* other)
{
	//Clear screen
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	player->draw();
	if (other != NULL) other->draw();
}
