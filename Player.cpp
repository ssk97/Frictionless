#include "Player.h"
Player::Player(double x2, double y2, double angle2)
{
    x = x2;
    y = y2;
    angle = angle2;
    xspd = yspd = aspd = 0;
    myExhaust = Exhaust();
    this->colorRed = 0;
}
double fRandGFX(double fMin, double fMax)
{
    std::uniform_real_distribution<double> dis(0, 1.0);
    return fMin + dis(rngGfx) * (fMax - fMin);
}
void Player::step()
{
    if (right_btn)
	aspd += .15;
    if (left_btn)
	aspd -= .15;
    if (up_btn) {
	xspd += xdir(angle, .05);
	yspd += ydir(angle, .05);
	myExhaust.add(x, y, xdir(angle,-5)+xspd, ydir(angle, -5)+yspd);
	myExhaust.add(x, y, xdir(angle + fRandGFX(-20, 20), -4.8) + xspd, ydir(angle + fRandGFX(-20, 20), -4.8) + yspd);
	myExhaust.add(x, y, xdir(angle + fRandGFX(-20, 20), -5.2) + xspd, ydir(angle + fRandGFX(-20, 20), -5.2) + yspd);
	myExhaust.add(x, y, xdir(angle + fRandGFX(-20, 20), -4.8) + xspd, ydir(angle + fRandGFX(-20, 20), -4.8) + yspd);
	myExhaust.add(x, y, xdir(angle + fRandGFX(-20, 20), -5.2) + xspd, ydir(angle + fRandGFX(-20, 20), -5.2) + yspd);
    }        
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

    myExhaust.step();
}
void Player::draw()
{
    myExhaust.draw();
    glPushMatrix();
    glTranslated(x, y, 0);
    glRotated(angle, 0, 0, 1);

    if (this->colorRed)
	glColor3f(1.0f, 0.0f, 0.0f);
    else
	glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(-10, -20);
        glVertex2f(0, 0);
        glVertex2f(0, 20);
        glVertex2f(10, -20);
    glEnd();//ship

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, xdir(frame*4,0.4)+.4); //pulsing blue
    glVertex2f(0, 0);
    glColor3f(0.0f, 0.0f, 1.0f); //blue
    for (int i = 0; i <= 36; i++) {
        glVertex2f(xdir(i * 10, 20), ydir(i * 10, 20));
    }
    glEnd();//shield

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 36; i++) {
        glColor3f(0.0f, 0.0f, xdir(frame * 4, 0.2) + .6); //pulsing blue
        glVertex2f(xdir(i * 10, 20), ydir(i * 10, 20));
        glColor3f(0.0f, 0.0f, 0.0f); //pulsing blue
        glVertex2f(xdir(i * 10, 30), ydir(i * 10, 30));
    }
    glEnd();//shield glow

    glDisable(GL_BLEND);

    glPopMatrix();
}

Player::~Player()
{
}

OtherPlayer::OtherPlayer(double x, double y, double angle, IPaddress ip)
        : Player(x, y, angle)
{
    ipAddr = ip;
    this->colorRed = 1;
}
