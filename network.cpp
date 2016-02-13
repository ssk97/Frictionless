#include <stdio.h>
#include "network.h"

#define PACKET_SIZE 1024

UDPsocket socket;
UDPpacket* packet;
IPaddress addr;

IPaddress server_begin()
{
    socket = SDLNet_UDP_Open(PORT_NUMBER);
    if (socket == NULL)
    {
	printf("Could not open socket: %s\n", SDLNet_GetError());
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
    return packet->address;
}

IPaddress client_begin(char* hostname)
{
    socket = SDLNet_UDP_Open(0);
    if (socket == NULL)
    {
	printf("Could not open socket: %s\n", SDLNet_GetError());	
	throw 445;
    }
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
    return packet->address;
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

void send_packet(ActivePlayer* play)
{
    struct data_sent data = {play->x, play->y, play->xspd, play->yspd, play->angle, play->aspd, play->left_prev, play->right_prev, play->up_prev};
    packet->data = (Uint8*) &data;
    packet->len = sizeof(data);
    if (SDLNet_UDP_Send(socket, -1, packet) == 0)
    {
	printf("Something went wrong. D:\n");
	throw 44;
    }
    return;	
}
