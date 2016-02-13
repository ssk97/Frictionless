#include <SDL.h>
#include <SDL_net.h>
#include "network.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
	printf("Usage: progname ip-address message");
	exit(1);
    }
    SDL_Init(0);
    SDLNet_Init();
    
    UDPsocket socket = SDLNet_UDP_Open(0);
    IPaddress serverAddr;
    SDLNet_ResolveHost(&serverAddr, argv[1], PORT_NUMBER);

    return sendPacket(serverAddr, (Uint8 *)argv[2], strlen(argv[2]), socket);
}
