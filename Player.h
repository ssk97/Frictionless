#pragma once
#include "globals.h"
class Player
{
public:
	Player(double x, double y, double angle);
	~Player();
	void step();
	void draw();
	void input(bool right, bool left, bool up);
	double x, y, xspd, yspd, angle, aspd;

	void setupDrawing();
	GLuint setupGeometry();
	GLuint setupVertexShader();
	GLuint setupFragmentShader();
	GLuint shaderProgram, vertexShader, fragmentShader, posAttrib, uniTrans, vbo, vao;
};

