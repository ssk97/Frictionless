#include "RingMaster.h"



RingMaster::RingMaster()
{
}


RingMaster::~RingMaster()
{
}



void Exhaust::step(double x, double y)//input: player x, player y
{
	
}
void Exhaust::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 36; i++) {
		glColor3f(xdir(frame * 4, 0.2) + .2, 0.0f, 0.0f); //pulsing red
		glVertex2f(xdir(i * 10, 20), ydir(i * 10, 20));
		glColor3f(.8, 0.0f, 0.0f); //pulsing red
		glVertex2f(xdir(i * 10, 30), ydir(i * 10, 30));
	}
	glEnd();//ring inward

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 36; i++) {
		glColor3f(xdir(frame * 4, 0.2) + .2, 0.0f, 0.0f); //pulsing red
		glVertex2f(xdir(i * 10, 40), ydir(i * 10, 40));
		glColor3f(.8, 0.0f, 0.0f); //pulsing red
		glVertex2f(xdir(i * 10, 30), ydir(i * 10, 30));
	}
	glEnd();//ring outward


	glDisable(GL_BLEND);
}