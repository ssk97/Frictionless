#pragma once
//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;


//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

static double xdir(double angle, double distance) {
	return sin((angle * M_PI) / 180)*distance;
}
static double ydir(double angle, double distance) {
	return cos((angle * M_PI) / 180)*distance;
}