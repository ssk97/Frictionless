#pragma once
#include "globals.h"
#define LIFESPAN 15
#define MAX_PARTICLES (LIFESPAN*10)
struct particle
{
	int framelife;
	double x, y, xspd, yspd;
};
class Exhaust
{
public:
	Exhaust();
	~Exhaust();
	void step();
	void draw();
	void add(double x, double y, double xspd, double yspd);
private:
	particle particles[MAX_PARTICLES];
	int insertpoint = 0;//insert particles at this point
};