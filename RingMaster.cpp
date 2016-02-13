#include "RingMaster.h"

double fRand(double fMin, double fMax)
{
    std::uniform_real_distribution<double> dis(0, 1.0);
    return fMin + dis(rngGame) * (fMax - fMin);
}
bool distWithin(double x1, double y1, double x2, double y2, double dist)
{
    return (((x1 - x2)*(x1 - x2)) + ((y1 - y2)*(y1 - y2))) <= (dist*dist);
}

RingMaster::RingMaster()
{
}

void RingMaster::init()
{
    double lastx = 100, lasty = 100;
    for (int i = 0; i < RING_MAX; i++) {
        double x = lastx, y = lasty;
        while (distWithin(x, y, lastx, lasty, 200)) {
            x = fRand(0 + 50, SCREEN_WIDTH - 50);
            y = fRand(0 + 50, SCREEN_HEIGHT - 50);
        }
        rings[i] = { x,y, -60 };
        lastx = x;
        lasty = y;
    }
}

RingMaster::~RingMaster()
{
}



void RingMaster::step(double x, double y)//input: player x, player y
{
    if (distWithin(x, y, rings[thisRing].x, rings[thisRing].y, 50)) {
        rings[thisRing++].status = 0;
    }
    if (thisRing < 19 && rings[thisRing+1].status < -1) {
        rings[thisRing+1].status++;
    }
}
void drawRing(double x, double y, double size1, double size2, double size3, float color)
{
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 36; i++) {
        glColor3f(0.0f, 0.0f, 0.0f); //pulsing red
        glVertex2f(x + xdir(i * 10, size1), y + ydir(i * 10, size1));
        glColor3f(color, 0.0f, 0.0f);
        glVertex2f(x + xdir(i * 10, size2), y + ydir(i * 10, size2));
    }
    glEnd();//ring inward

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 36; i++) {
        glColor3f(0.0f, 0.0f, 0.0f); //pulsing red
        glVertex2f(x + xdir(i * 10, size3), y + ydir(i * 10, size3));
        glColor3f(color, 0.0f, 0.0f);
        glVertex2f(x + xdir(i * 10, size2), y + ydir(i * 10, size2));
    }
    glEnd();//ring outward
}
void RingMaster::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    for (int r = 0; r < thisRing; r++) {//expanding rings
        double expand = rings[r].status++;
        drawRing(rings[r].x, rings[r].y, 15 + expand, 30 + expand, 45 + expand, .8 - expand / 500);
    }
    double x = rings[thisRing].x, y = rings[thisRing].y;
    drawRing(x, y, 15 + xdir(frame * 4, -5), 30, 45 + xdir(frame * 4, 5), .8);

    if (thisRing < 19) {
        double expand = rings[thisRing + 1].status;

        drawRing(rings[thisRing + 1].x, rings[thisRing + 1].y, 15, 30, 45, .3 + expand / 200);

        glBegin(GL_LINE_STRIP);
        glColor3f(1, 1, 1);
        glVertex2f(x, y);
        glColor3f(.4, .4, .4);
        glVertex2f(rings[thisRing + 1].x, rings[thisRing + 1].y);
        if (thisRing < 18) {
            glColor3f(.4, .4, .4);
            glVertex2f(rings[thisRing + 1].x, rings[thisRing + 1].y);
            glColor3f(0, 0, 0);
            glVertex2f(rings[thisRing + 2].x, rings[thisRing + 2].y);
        }
        glEnd();
    }
    glDisable(GL_BLEND);
}