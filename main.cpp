/*Much of the code in this file was originally from Lazy Foo' Productions
(http://lazyfoo.net/)*/
#include "globals.h"
#include "Player.h"
#include "GameLogic.h"
#include "network.h"
#include "Menu.h"
#include <vector>
#include <cstdint>
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
bool init(int screen)//0 = windowed (default), 1 = 1.5x screen, 2 = fullscreen, 3 = 1.5x fullscreen mode
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
        switch (screen) {
        case 1:
            gWindow = SDL_CreateWindow("Frictionless", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH*1.5, SCREEN_HEIGHT*1.5, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
            break;
        case 2:
            gWindow = SDL_CreateWindow("Frictionless", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
            break;
        case 3:
            gWindow = SDL_CreateWindow("Frictionless", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH*1.5, SCREEN_HEIGHT*1.5, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
            break;
        default:
            gWindow = SDL_CreateWindow("Frictionless", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        }
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

Sint32 mouseX, mouseY;
bool clicked;

#define STATE_MENU 0
#define STATE_BEGINGAME 1
#define STATE_WAIT_FOR_CLIENT 2
#define STATE_GAMEPLAY 3
#include <time.h>
int main(int argc, char* args[])
{
    //Start up SDL and create window
    int screenmode = 0;
    if (argc > 1) {
        screenmode = std::stoi(args[1]);
    }
    if (!init(screenmode))
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        Menu menu = Menu();
        //Load media
        if (!menu.init())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            //Main loop flag
            bool quit = false;
            int state = STATE_MENU;
            int mode = M_SINGLEPLAYER;

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
                endTime = endTime + 17;
                frame++;
                if (frame % 3 == 0) endTime--;
                //Handle events on queue
                SDL_Scancode keydown = SDL_SCANCODE_UNKNOWN;
                while (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    if (e.type == SDL_MOUSEMOTION) {
                        //Get the mouse offsets 
                        mouseX = e.motion.x;
                        mouseY = e.motion.y;
                        if (screenmode == 1 || screenmode == 3) {
                            mouseX /= 1.5;
                            mouseY /= 1.5;
                        }
                    }
                    if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                        mouseX = e.button.x;
                        mouseY = e.button.y;
                        if (e.button.button == SDL_BUTTON_LEFT)
                            clicked = (e.button.state == SDL_PRESSED);
                        if (screenmode == 1 || screenmode == 3) {
                            mouseX /= 1.5;
                            mouseY /= 1.5;
                        }
                    }
                    if (e.type == SDL_KEYDOWN) {
                        keydown = e.key.keysym.scancode;
                    }
                }
                if (keyboard[SDL_SCANCODE_ESCAPE]) {
                    quit = true;
                }
                //Clear screen
                glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                switch (state) {
                    case STATE_MENU:
                        g = GameLogic();
                        g.write_other_players = SDL_CreateMutex();		  
                        mode = menu.step( mouseX,  mouseY,  clicked, keyboard, keydown);//returns mode if changed, 0 if no change
                        if (mode != 0) {
                            std::cout << mode;
			                state = (mode == M_SERVER) ? STATE_WAIT_FOR_CLIENT : STATE_BEGINGAME;
                        }
                        menu.draw( mouseX,  mouseY);
                        break;
		            case STATE_WAIT_FOR_CLIENT:
			            uint32_t rng_seed;
			            IPaddress ip;
                        menu.draw_text(80, 300, "Waiting for client");
                        menu.draw_text(180, 400, "to connect");
			            if (server_begin(&rng_seed, &ip))
			            {
			                state = STATE_BEGINGAME;
			                g.addOtherPlayer(100, 100, 0, ip);
			                rngGame.seed(rng_seed);
			                SDL_CreateThread(receive_packets, "Network", &g);
			            }
		                break;
                    case STATE_BEGINGAME:
                        if (mode == M_CLIENT)
                        {
                            //Client
                            uint32_t rng_seed = time(NULL);
                            g.addOtherPlayer(100, 100, 0, client_begin(menu.tmpip, rng_seed));
                            rngGame.seed(rng_seed);
                            SDL_CreateThread(receive_packets, "Network", &g);
                        }
                        if (mode == M_SINGLEPLAYER)
                        {
                            rngGame.seed(time(NULL));
                        }
                        g.rings.init();
                        state = STATE_GAMEPLAY;//don't break, continue directly to gameplay
                    case STATE_GAMEPLAY: 
                        g.step(keyboard);
                        g.draw();
                        if (g.rings.thisRing >= 20) {
                            menu.draw_text(10, 10, "You won");
                            menu.draw_text(10, 110, "Time taken:");
                            menu.draw_text(10 + chrw * 11, 110, const_cast<char *>((std::to_string(g.timeFlying)).c_str()));
                            menu.draw_text(10, 200, "Press Enter to return");
                            menu.draw_text(10, 300, "to menu");
                            if (keydown == SDL_SCANCODE_RETURN) {
                                state = STATE_MENU;
                                if (mode == M_CLIENT || mode == M_SERVER)
                                    server_stop();
                                //FREE STUFF
                            }
                        }
                        else {
                            if (g.rings.thisRing >= 10)
                                menu.draw_text(10, 10, const_cast<char *>((std::to_string(g.rings.thisRing)).c_str()));
                            else
                                menu.draw_text(10 + chrw, 10, const_cast<char *>((std::to_string(g.rings.thisRing)).c_str()));
                            menu.draw_text(10 + 2 * chrw, 10, "/20");
                        }
                        break;
                    }
                menu.drawGrid();
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
