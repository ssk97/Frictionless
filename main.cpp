/*Much of the code in this file was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
#include "globals.h"
#include "Player.h"
#include "GameLogic.h"
#include "network.h"
#include <vector>
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

unsigned long frame;
std::mt19937 rngGame, rngGfx;
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
        gWindow = SDL_CreateWindow("Frictionless", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);// | SDL_WINDOW_FULLSCREEN);
        SDLNet_Init();
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
                if (SDL_GL_SetSwapInterval(0) < 0)
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
    GLuint TextureID = 0;

    // You should probably use CSurface::OnLoad ... ;)
    //-- and make sure the Surface pointer is good!
    SDL_Surface* Surface = IMG_Load("Button.png");
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
#define STATE_BEGINGAME 1
#define STATE_GAMEPLAY 2
#include <time.h>
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
            int state = STATE_BEGINGAME;


            rngGfx.seed(time(NULL));

            glLoadIdentity();
            glTranslated(-1, 1, 0);
            glScaled(2.0 / SCREEN_WIDTH, -2.0 / SCREEN_HEIGHT, 1.0);

            const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
            //Event handler
            SDL_Event e;
            frame = 0;
            unsigned int endTime = SDL_GetTicks();

            GameLogic g;
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
                    glEnable(GL_TEXTURE_2D);
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glBegin(GL_QUADS);
                    //glColor3d(1, 0, 0); 
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex2f(100, 500);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex2f(740, 500);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex2f(740, 100);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex2f(100, 100);
                    glEnd();
                break;
                case STATE_BEGINGAME:
                rngGame.seed(time(NULL));
                g = GameLogic();
                g.write_other_players = SDL_CreateMutex();
                if (argc == 2)
                {
                    //Server
                    g.addOtherPlayer(100, 100, 0, server_begin());
                    SDL_CreateThread(receive_packets, "Network", &g);
                }
                if (argc == 3)
                {
                    //Client
                    g.addOtherPlayer(100, 100, 0, client_begin(args[2]));
                    SDL_CreateThread(receive_packets, "Network", &g);
                }
                state = STATE_GAMEPLAY;//don't break, continue directly to gameplay
                case STATE_GAMEPLAY: 
                g.step(keyboard);
                g.draw();
                break;
                }
                //Update screen
                SDL_GL_SwapWindow(gWindow);
                if (SDL_GetTicks() < endTime) {
                    //Sleep the remaining frame time
                    SDL_Delay(endTime-SDL_GetTicks());
                }
                else {
                    //std::cout << SDL_GetTicks()-endTime << "\n";
                }
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
