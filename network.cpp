#include <stdio.h>
#include "network.h"

#define PACKET_SIZE 1024

UDPsocket socket;
UDPpacket* packet;
IPaddress addr;

void server_begin()
{
    socket = SDLNet_UDP_Open(PORT_NUMBER);
    if (socket == NULL)
    {
	printf("Could not open socket.");
	throw 8;
    }
    packet = SDLNet_AllocPacket(PACKET_SIZE);
    int ready = 0;
    while(!ready)
    {
	if(SDLNet_UDP_Recv(socket,packet))
	{
	    //Do something with packet->data and packet->len
	    addr = packet->address;
	    ready = 1;
	}
    }
    return;
}

void client_begin(char* hostname)
{
    socket = SDLNet_UDP_Open(0);
    SDLNet_ResolveHost(&addr, hostname, PORT_NUMBER);
    packet = SDLNet_AllocPacket(PACKET_SIZE);
    if (!packet)
    {
	printf("Invalid packet.\n");
	throw 15;
    }
    packet->address.host = addr.host;
    packet->address.port = PORT_NUMBER;
    //TODO: Transmit some real information over the wire.
    packet->data = (Uint8*) "hi";
    packet->len = 10;

    if (SDLNet_UDP_Send(socket, -1, packet) == 0)
    {
	printf("Something went wrong. :(\n");
	throw 4454;
    }
    return;
}

//This needs to be run in a seperate thread.
void receive_packets()
{
    while(1)
    {
	if (SDLNet_UDP_Recv(socket,packet))
	{
	    printf("We have a packet!");
	}
    }
}

void send_packet()
{
    packet->data = (Uint8*) "ho";
    packet->len = 10;
    if (SDLNet_UDP_Send(socket, -1, packet) == 0)
    {
	printf("Something went wrong. D:\n");
	throw 44;
    }
    return;	
}
