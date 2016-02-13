#include "Player.h"

Player::Player(double x2, double y2, double angle2)
{
	x = x2;
	y = y2;
	angle = angle2;
	xspd = yspd = aspd = 0;
	keyboard = SDL_GetKeyboardState(NULL);
}
void Player::step()
{
	if (keyboard[SDL_SCANCODE_RIGHT])
		aspd -= .2;
	if (keyboard[SDL_SCANCODE_LEFT])
		aspd += .2;
	if (keyboard[SDL_SCANCODE_UP]) {
		xspd += xdir(angle,.1);
		yspd += ydir(angle, .1);
	}
	x += xspd;
	y += yspd;
	angle += aspd;
}
void Player::draw()
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(gRenderer, x+xdir(angle,10), y+ ydir(angle, 10), x + xdir(angle, -10), y + ydir(angle, -10));
	SDL_RenderDrawLine(gRenderer, x, y, x + xdir(angle+135, 10), y + ydir(angle+135, 10));
	SDL_RenderDrawLine(gRenderer, x, y, x + xdir(angle - 135, 10), y + ydir(angle - 135, 10));
}

Player::~Player()
{
}
