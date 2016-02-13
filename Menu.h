#pragma once
#include "globals.h"

#define M_SINGLEPLAYER 1
#define M_CLIENT 2
#define M_SERVER 3

class Menu
{
public:
    int step(Sint32 mouseX, Sint32 mouseY, bool clicked);//returns mode if changed, 0 if no change
    void draw(Sint32 mouseX, Sint32 mouseY);
    Menu();
    ~Menu();
};

