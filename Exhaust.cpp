#include "Exhaust.h"



Exhaust::Exhaust()
{
}

Exhaust::~Exhaust()
{
}

void Exhaust::step()
{
	int i = insertpoint;
	while(particles[i].framelife > 0) {
		particles[i].x += particles[i].xspd;
		particles[i].y += particles[i].yspd;
		particles[i].framelife--;
		i--;
		if (i < 0) {
			i += MAX_PARTICLES;
		}
	}
}
void Exhaust::add(double x, double y, double xspd, double yspd)
{
	insertpoint++;
	if (insertpoint >= MAX_PARTICLES)
		insertpoint = 0;
	particles[insertpoint] = { 60,x, y, xspd, yspd };
}
void Exhaust::draw()
{
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	int i = insertpoint;
	while (particles[i].framelife > 0) {
		glColor3f(particles[i].framelife/120.0f+.5f , particles[i].framelife / 120.0f + .5f, 0.0f); //yellow, fading
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(particles[i].x , particles[i].y);
		glColor3f(particles[i].framelife / 120.0f + .5f, 0.0f, 0.0f); //red, fading
		for (int i = 0; i <= 36; i++) {
			glVertex2f(particles[i].x+xdir(i * 10, 10), particles[i].y + ydir(i * 10, 10));
		}
		glEnd();//shield
	}

	glDisable(GL_BLEND);


	glPopMatrix();
}