#include <SDL_net.h>
#define PORT_NUMBER 1028
int server();

int sendPacket(IPaddress, Uint8*, int, UDPsocket, UDPpacket*);
