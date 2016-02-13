#pragma once
#include "globals.h"

#define M_SINGLEPLAYER 1
#define M_CLIENT 2
#define M_SERVER 3

#define s_main 1
#define s_clientIP 2
class Menu
{
public:
    int step(Sint32 mouseX, Sint32 mouseY, bool clicked);//returns mode if changed, 0 if no change
    void draw(Sint32 mouseX, Sint32 mouseY);
    bool init();//load all the files into surfaces into openGL textures
    Menu();
    ~Menu();
    int substate = s_main;
    Uint64 tmpip;
};

