#include <stdio.h>
#include "network.h"

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
	    printf("We got a packet!]n");
	}
    }
    return 0;
}

int sendPacket(IPaddress addr, Uint8* message, int messageLength, UDPsocket socket)
{
    printf("About to alloc.");
    UDPpacket *p = SDLNet_AllocPacket(PACKET_SIZE);
    if (!p)
    {
	printf("Could not allocate packet.\n");
	return -1;
    }
    p->address.host = addr.host;
    p->address.port = PORT_NUMBER;
    p->data = message;
    p->len = messageLength;

    int err = 0;
    printf("About to send");
    if (SDLNet_UDP_Send(socket, -1, p) == 0) err = -1;

    printf("About to free");
    //SDLNet_FreePacket(p);
    return err;
}
