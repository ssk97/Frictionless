#include <SDL_net.h>
#define PORT_NUMBER 1028

UDPsocket socket();

int server();
void server_begin();

int sendPacket(IPaddress, Uint8*, int, UDPsocket, UDPpacket*);
