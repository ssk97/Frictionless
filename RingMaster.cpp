#include "RingMaster.h"

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}
bool distWithin(double x1, double y1, double x2, double y2, double dist)
{
	return (((x1 - x2)*(x1 - x2)) + ((y1 - y2)*(y1 - y2))) <= (dist*dist);
}

RingMaster::RingMaster()
{
	for (int i = 0; i < RING_MAX; i++) {
		rings[i] = { fRand(0 + 50,SCREEN_WIDTH - 50),fRand(0 + 50,SCREEN_HEIGHT - 50) };
	}
}


RingMaster::~RingMaster()
{
}



void RingMaster::step(double x, double y)//input: player x, player y
{
	if (distWithin(x, y, rings[thisRing].x, rings[thisRing].y, 40)) {
		thisRing++;
	}
}
void RingMaster::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	double x = rings[thisRing].x, y = rings[thisRing].y;
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 36; i++) {
		glColor3f(xdir(frame * 4, 0.2) + .4, 0.0f, 0.0f); //pulsing red
		glVertex2f(x+xdir(i * 10, 20), y+ydir(i * 10, 20));
		glColor3f(.8, 0.0f, 0.0f); //pulsing red
		glVertex2f(x + xdir(i * 10, 30),y+ ydir(i * 10, 30));
	}
	glEnd();//ring inward

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 36; i++) {
		glColor3f(xdir(frame * 4, 0.2) + .4, 0.0f, 0.0f); //pulsing red
		glVertex2f(x + xdir(i * 10, 40), y+ydir(i * 10, 40));
		glColor3f(.8, 0.0f, 0.0f); //pulsing red
		glVertex2f(x + xdir(i * 10, 30), y+ydir(i * 10, 30));
	}
	glEnd();//ring outward


	glDisable(GL_BLEND);
}