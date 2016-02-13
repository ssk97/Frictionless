#include <stdio.h>
#include "network.h"

#define PORT_NUMBER 1028
#define PACKET_SIZE 1024

//Returns non-zero on failure
int server()
{
    UDPsocket socket = SDLNet_UDP_Open(PORT_NUMBER);
    if (socket == NULL)
    {
	printf("Could not open socket.");
	return -1;	
    }
    UDPpacket* packet = SDLNet_AllocPacket(PACKET_SIZE);
    int quit = 0;
    while(!quit)
    {
	if (SDLNet_UDP_Recv(socket, packet))
	{
	    //Stub.
	    printf("We got a packet!");
	}
    }
    return 0;
}

int sendPacket(IPaddress addr, Uint8* message, int messageLength, UDPsocket socket)
{
    UDPpacket *p = SDLNet_AllocPacket(PACKET_SIZE);
    p->address.host = addr.host;
    p->address.port = addr.port;
    p->data = message;
    p->len = messageLength;

    int err = 0;
    if (SDLNet_UDP_Send(socket, -1, p) == 0) err = -1;

    SDLNet_FreePacket(p);
    return err;
}
