#include "Player.h"
void Player::setupDrawing() {
	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);//this is bound to the geometry setup in the next call
	setupGeometry();//sets up vbo

	shaderProgram = glCreateProgram();
	vertexShader = setupVertexShader();
	glAttachShader(shaderProgram, vertexShader);
	fragmentShader = setupFragmentShader();
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);


	uniTrans = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(view));
}
GLuint Player::setupGeometry() {
	const int count = 40;
	float vertices[count * 2 + 8] = {
		10, 20,
		0, -20,
		0, 0,
		-10, 20,

		0, 0 //initial points of circle
	};
	int vertexNum = 8+2;
	for (int i = 0; i < count - 1; i += 1) {
		vertices[vertexNum++] = (float)xdir((i * 360 / (count - 2)),40);
		vertices[vertexNum++] = (float)ydir((i * 360 / (count - 2)),40);
	}
	glGenBuffers(1, &vbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	return vbo;
}
GLuint Player::setupVertexShader() {
	const GLchar* vertexSource =
		"#version 330 core\n"
		"in vec2 position;"
		"uniform mat4 trans;"
		"uniform mat4 view;"
		"void main() {"
		" gl_Position = view*trans*vec4(position, 0.0, 1.0);"//xyzw
		"}";
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	checkShader(vertexShader);
	return vertexShader;
}
GLuint Player::setupFragmentShader() {
	const GLchar* fragmentSource =
		"#version 330 core\n"
		"out vec4 outColor;"
		"void main() {"
		" outColor = vec4(1.0, 0.0, 0.0, 1.0);"//RGBA
		"}";
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	checkShader(fragmentShader);
	return fragmentShader;
}
Player::Player(double x2, double y2, double angle2)
{
	x = x2;
	y = y2;
	angle = angle2;
	xspd = yspd = aspd = 0;
	setupDrawing();
}
void Player::input(bool right, bool left, bool up)
{
	if (right)
		aspd -= .15;
	if (left)
		aspd += .15;
	if (up) {
		xspd += xdir(angle, .05);
		yspd += ydir(angle, .05);
	}
}
void Player::step()
{
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
}
void Player::draw()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");

	glm::mat4 trans, rot;
	trans = glm::translate(trans, glm::vec3((float)x, (float)y, 0.0));
	rot = glm::rotate(trans, (float)angle, glm::vec3(0.0, 0.0, 1.0));
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(rot));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 48);

}

Player::~Player()
{
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
}
