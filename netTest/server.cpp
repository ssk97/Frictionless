#include <SDL.h>
#include <SDL_net.h>
#include "network.h"

int main(int argc, char* argv[])
{
    SDL_Init(0);
    SDLNet_Init();

    server();
}

