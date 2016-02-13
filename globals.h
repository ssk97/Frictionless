#pragma once
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL_opengl.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

//The window we'll be rendering to
extern SDL_Window* gWindow;
extern SDL_GLContext gContext;

extern void checkShader(GLuint shader);
extern void checkErrors();

static double xdir(double angle, double distance) {
	return -sin((angle * M_PI) / 180)*distance;
}
static double ydir(double angle, double distance) {
	return cos((angle * M_PI) / 180)*distance;
}