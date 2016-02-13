#pragma once
#include "globals.h"

#define M_SINGLEPLAYER 1
#define M_CLIENT 2
#define M_SERVER 3

#define s_main 1
#define s_clientIP 2

static double chrw = 865 / 9. / 2;//font width
static double chrh = 1332 / 11. / 2;//font height
static double texw = 1 / 9.;
static double texh = 1 / 11.;
class Menu
{
public:
    int step(Sint32 mouseX, Sint32 mouseY, bool clicked, const Uint8 *keyboard, SDL_Scancode keypressed);//returns mode if changed, 0 if no change
    void draw(Sint32 mouseX, Sint32 mouseY);
    bool init();//load all the files into surfaces into openGL textures
    void drawGrid();
    void draw_char(double x, double y, char c);
    void draw_text(double x, double y, char* arr);
    Menu();
    ~Menu();
    int substate = s_main;
    char tmpip[30] = "";
    int ippos = 0;
    SDL_Scancode lk;
};

