#include "Menu.h"



Menu::Menu()
{
}


Menu::~Menu()
{
}
int Menu::step(Sint32 mouseX, Sint32 mouseY, bool clicked){//returns mode if changed, 0 if no change
    if (clicked) {
        if (mouseY < 300)
            return M_SINGLEPLAYER;
        else if (mouseY > 450)
            return M_SERVER;
        else
            return M_CLIENT;
    }
    return 0;
}
void Menu::draw(Sint32 mouseX, Sint32 mouseY) {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    //glColor3d(1, 0, 0); 
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(172, 584);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(812, 584);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(812, 184);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(172, 184);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}