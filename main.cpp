/*Much of the code in this file was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/

#include "globals.h"
#include "Player.h"
//Starts up SDL and creates window
bool init();

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();
bool initGL();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;
SDL_GLContext gContext;

void checkShader(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		std::cout << buffer;
	}
}
void checkErrors()
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "OPEN GL ERROR!" << err;
	}
}

unsigned long frame;
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				//Initialize OpenGL
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}

	return success;
}

bool initGL()
{
	GLenum error = GL_NO_ERROR;

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! %s\n"<<error;
		return false;
	}

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! %s\n" << error;
		return false;
	}

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! %s\n" << error;
		return false;
	}

	if (glewInit() != GLEW_OK) {
		std::cerr << "Error initializing glew! %s\n" << error;
		return false;
	}
	glEnable(GL_MULTISAMPLE);

	return true;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

#define STATE_MENU 0
#define STATE_GAMEPLAY 1
int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;
			int state = STATE_GAMEPLAY;
			Player * p = new Player(100, 100, 0);
			
			glLoadIdentity();
			glTranslated(-1, 1, 0);
			glScaled(2.0 / SCREEN_WIDTH, -2.0 / SCREEN_HEIGHT, 1.0);

			const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
			//Event handler
			SDL_Event e;
			frame = 0;
			unsigned int endTime = SDL_GetTicks();
			//While application is running
			while (!quit)
			{
				endTime = endTime +17;
				frame++;
				if (frame % 3 == 0) endTime--;
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				if (keyboard[SDL_SCANCODE_ESCAPE])
					quit = true;
				switch (state) {
					case STATE_MENU: 
						break;
					case STATE_GAMEPLAY: 
						p->input(keyboard[SDL_SCANCODE_RIGHT], keyboard[SDL_SCANCODE_LEFT], keyboard[SDL_SCANCODE_UP]);
						p->step();
						//Clear screen
						glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
						glClear(GL_COLOR_BUFFER_BIT);
						p->draw();
						break;
				}
				//Update screen
				SDL_GL_SwapWindow(gWindow);
				if (SDL_GetTicks() < endTime) {
					//Sleep the remaining frame time
					SDL_Delay(endTime-SDL_GetTicks());
				}
				else {
					std::cout << SDL_GetTicks()-endTime << "\n";
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}