#include "Player.h"
Player::Player(double x2, double y2, double angle2)
{
	x = x2;
	y = y2;
	angle = angle2;
	xspd = yspd = aspd = 0;
}
void Player::input(bool right, bool left, bool up)
{
	if (right)
		aspd += .15;
	if (left)
		aspd -= .15;
	if (up) {
		xspd += xdir(angle, .05);
		yspd += ydir(angle, .05);
	}
}
void Player::step()
{
	x += xspd;
	y += yspd;
	angle += aspd;
	if (x < 0 || x > SCREEN_WIDTH) {
		x -= xspd;
		xspd *= -1;
	}
	if (y < 0 || y > SCREEN_HEIGHT) {
		y -= yspd;
		yspd *= -1;
	}
}
void Player::draw()
{
	glPushMatrix();
	glTranslated(x, y, 0);
	glRotated(angle, 0, 0, 1);
	glColor3f(0.0f, 0.0f, 1.0f); //blue color
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(-10, -20);
		glVertex2f(0, 0);
		glVertex2f(0, 20);
		glVertex2f(10, -20);
	glEnd();//ship
	glPopMatrix();
}

Player::~Player()
{
}
