#include "Menu.h"



Menu::Menu()
{
}


Menu::~Menu()
{
}

double w = 865 / 9./2;//font width
double h = 1332 / 11./2;//font height
double texw = 1 / 9.;
double texh = 1 / 11.;

bool Menu::init() {
    GLuint TextureID = 0;

    // You should probably use CSurface::OnLoad ... ;)
    //-- and make sure the Surface pointer is good!
    SDL_Surface* Surface = IMG_Load("joystix_monospace-regular.png");
    if (Surface == NULL)
    {
        std::cerr << "Unable to load image Button.png! SDL_image Error: " << IMG_GetError() << "\n";
        return false;
    }
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    int Mode = GL_RGB;

    if (Surface->format->BytesPerPixel == 4) {
        Mode = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}
void draw_char(double x, double y, char c) {
    int id = -1;
    if (c >= '0' && c <= '9') id = c - '0';
    if (c >= 'A' && c <= 'Z') id = c - 'A' + 10;
    if (c >= 'a' && c <= 'z') id = c - 'a' + 10;
    if (id != -1) {
        double charx = (id % 9)*texw;
        double chary = (id / 9)*texh;
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(charx, chary+texh);
        glVertex2f(x, y + h);
        glTexCoord2f(charx+texw, chary + texh);
        glVertex2f(x + w, y + h);
        glTexCoord2f(charx + texw, chary);
        glVertex2f(x + w, y);
        glTexCoord2f(charx, chary);
        glVertex2f(x, y);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
}
void draw_text(double x, double y, char* arr) {
    int i = 0;
    while (arr[i] != 0) {
        draw_char(x + i*w, y, arr[i]);
        i++;
    }
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
    draw_text(100, 100, "Single Player");
    draw_text(100, 300, "Client Game");
    draw_text(100, 500, "Server Game");
}

void draw_round_rect(double x, double y, double w, double h) {

}