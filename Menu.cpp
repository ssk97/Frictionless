#include "Menu.h"



Menu::Menu()
{
}


Menu::~Menu()
{
}

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
void Menu::drawGrid() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    for (double x = ((frame % 80)/2); x < SCREEN_WIDTH+20; x += 40) {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(x - 10, 0);
        glVertex2f(x - 10, SCREEN_HEIGHT);
        glColor3f(0.05f, 0.05f, xdir(frame * 4, 0.05) + .2); //pulsing blue
        glVertex2f(x, 0);
        glVertex2f(x, SCREEN_HEIGHT);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(x + 10, 0);
        glVertex2f(x + 10, SCREEN_HEIGHT);
        glEnd();//shield
    }
    for (double y = ((frame % 80) / 2); y < SCREEN_HEIGHT + 20; y += 40) {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0, y-10);
        glVertex2f(SCREEN_WIDTH,y-10);
        glColor3f(0.05f, 0.05f, xdir(frame * 4, 0.05) + .2); //pulsing blue
        glVertex2f(0, y);
        glVertex2f(SCREEN_WIDTH, y);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0, y+10);
        glVertex2f(SCREEN_WIDTH, y+10);
        glEnd();//shield
    }
    glDisable(GL_BLEND);
}
void Menu::draw_char(double x, double y, char c) {
    int id = -1;
    if (c >= '0' && c <= '9') id = c - '0';
    if (c >= 'A' && c <= 'Z') id = c - 'A' + 10;
    if (c >= 'a' && c <= 'z') id = c - 'a' + 10;
    if (c == '.') id = 80;
    if (c == '/') id = 68;
    if (c == ':') id = 81;
    if (id != -1) {
        double charx = (id % 9)*texw;
        double chary = (id / 9)*texh;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(charx, chary+texh);
        glVertex2f(x, y + chrh);
        glTexCoord2f(charx+texw, chary + texh);
        glVertex2f(x + chrw, y + chrh);
        glTexCoord2f(charx + texw, chary);
        glVertex2f(x + chrw, y);
        glTexCoord2f(charx, chary);
        glVertex2f(x, y);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    }
}
void Menu::draw_text(double x, double y, char* arr) {
    int i = 0;
    while (arr[i] != 0) {
        draw_char(x + i*chrw, y, arr[i]);
        i++;
    }
}

int Menu::step(Sint32 mouseX, Sint32 mouseY, bool clicked, const Uint8 *keyboard, SDL_Scancode keypressed){//returns mode if changed, 0 if no change
    switch (substate) {
        case s_main:
            if (clicked) {
                if (bbox(mouseX, mouseY, 100, 100, chrw * 13, chrh)) {
                    return M_SINGLEPLAYER;
                }
                if (bbox(mouseX, mouseY, 100, 300, chrw * 11, chrh)) {
                    substate = s_clientIP;
                }
                if (bbox(mouseX, mouseY, 100, 500, chrw * 11, chrh)) {
                    return M_SERVER;
                }
            }
            break;
        case s_clientIP:
            if (ippos > 20) ippos = 20;
            if (keypressed == SDL_SCANCODE_0) {
                tmpip[ippos++] = '0';
            }
            else if (keypressed == SDL_SCANCODE_1) {
                tmpip[ippos++] = '1';
            }
            else if (keypressed == SDL_SCANCODE_2) {
                tmpip[ippos++] = '2';
            }
            else if (keypressed == SDL_SCANCODE_3) {
                tmpip[ippos++] = '3';
            }
            else if (keypressed == SDL_SCANCODE_4) {
                tmpip[ippos++] = '4';
            }
            else if (keypressed == SDL_SCANCODE_5) {
                tmpip[ippos++] = '5';
            }
            else if (keypressed == SDL_SCANCODE_6) {
                tmpip[ippos++] = '6';
            }
            else if (keypressed == SDL_SCANCODE_7) {
                tmpip[ippos++] = '7';
            }
            else if (keypressed == SDL_SCANCODE_8) {
                tmpip[ippos++] = '8';
            }
            else if (keypressed == SDL_SCANCODE_9) {
                tmpip[ippos++] = '9';
            }
            else if (keypressed == SDL_SCANCODE_0) {
                tmpip[ippos++] = '0';
            }
            else if (keypressed == SDL_SCANCODE_PERIOD) {
                tmpip[ippos++] = '.';
            }
            else if (keypressed == SDL_SCANCODE_BACKSPACE) {
                if (ippos > 0) {
                    tmpip[--ippos] = 0;
                }
            }
            if (keypressed == SDL_SCANCODE_RETURN) {
                substate = s_main;
                return M_CLIENT;
            }
            break;
    }
    return 0;
}
void draw_round_rect(double x, double y, double w, double h, Sint32 mouseX, Sint32 mouseY) {
    double r = h / 2.;
    glBegin(GL_TRIANGLE_FAN);
    if (bbox(mouseX, mouseY, x, y, w, h)) {
        glColor3f(0.4f, 0.4f, 0.4f);
    } else {
        glColor3f(0.0f, 0.0f, 0.0f);
    }
    glVertex2f(x + w/2, y + h/2);
    if (bbox(mouseX, mouseY, x, y, w, h)) {
        glColor3f(0.8f, 0.8f, 0.8f);
    }
    else {
        glColor3f(0.6f, 0.6f, 0.6f);
    }
    glVertex2f(x+r, y);
    for (int i = 0; i <= 18; i++) {
        glVertex2f(x + w - r-xdir(i * 10, r), y + h/2 - ydir(i * 10, r));
    }
    for (int i = 18; i <= 36; i++) {
        glVertex2f(x + r - xdir(i * 10, r), y + h / 2 - ydir(i * 10, r));
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
void Menu::draw(Sint32 mouseX, Sint32 mouseY) {
    switch (substate) {
        case s_main:
            draw_round_rect(100, 100, chrw * 13, chrh, mouseX, mouseY);
            glColor3f(1.0f, .4f,.9f);
            draw_text(100, 100, "Single Player");
            draw_round_rect(100, 300, chrw * 11, chrh, mouseX, mouseY);
            glColor3f(1.0f, .4f, .9f);
            draw_text(100, 300, "Client Game");
            draw_round_rect(100, 500, chrw * 11, chrh, mouseX, mouseY);
            glColor3f(1.0f, .4f, .9f);
            draw_text(100, 500, "Server Game");
            break;
        case s_clientIP:
            glColor3f(1.0f, .4f, .9f);
            draw_text(100, 300, "IP address:");
            draw_text(100, 400, tmpip);
    }
}
