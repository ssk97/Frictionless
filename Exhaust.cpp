#include "Exhaust.h"



Exhaust::Exhaust()
{
    for (int i = 0; i < MAX_PARTICLES; i++)
        particles[i] = { 0,0,0,0,0 };
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
    particles[insertpoint] = { LIFESPAN,x, y, xspd, yspd };
}
void Exhaust::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    int i = insertpoint;
    while (particles[i].framelife > 0) {
        glColor3f(particles[i].framelife/(float)LIFESPAN, particles[i].framelife / (float)LIFESPAN, 0.0f); //yellow, fading
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(particles[i].x , particles[i].y);
        glColor3f(particles[i].framelife /(float)LIFESPAN, 0.0f, 0.0f); //red, fading
        for (int j = 0; j <= 36; j++) {
            glVertex2f(particles[i].x+xdir(j * 10, 10), particles[i].y + ydir(j * 10, 10));
        }
        glEnd();//ember
        i--;
        if (i < 0) {
            i += MAX_PARTICLES;
        }
    }

    glDisable(GL_BLEND);
}