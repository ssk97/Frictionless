#include "Bumper.h"
#include <cmath>

Bumper::Bumper(double x, double y, double width)
{
    this->x = x;
    this->y = y;
    this->width = width;
}

int Bumper::calculateCollision(double playerX, double playerY)
{
    if (!bbox(playerX, playerY, x, y, width, width))
    {
	return BUMPER_NO_COLLISION;
    }
    else
    {
	return BUMPER_X_COLLISION;
    }
}

void Bumper::draw()
{
    glPushMatrix();
    glColor3f(1.0f, 0.75f, .8f);
    glBegin(GL_QUADS);                      // Draw A Quad
    glVertex3f(x, y, 0.0f);              // Top Left
    glVertex3f(x, y + width, 0.0f);              // Top Right
    glVertex3f(x + width, y + width, 0.0f);              // Bottom Right
    glVertex3f(x + width,y + width, 0.0f);              // Bottom Left
    glEnd();
    glPopMatrix();
     
}

Bumper::~Bumper()
{
}
