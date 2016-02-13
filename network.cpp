#include <stdio.h>
#include "network.h"
#include "globals.h"
#include "GameLogic.h"

#define PACKET_SIZE 10000

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
	    printf("Got opening connection");
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
    packet->len = 200;

    if (SDLNet_UDP_Send(socket, -1, packet) == 0)
    {
	printf("Something went wrong: %s\n", SDLNet_GetError());
	throw 4454;
    }
    return packet->address;
}

//This needs to be run in a seperate thread.
int receive_packets(void* gameLogic)
{
    printf("Starting to recieve packets");
    while(1)
    {
	SDL_Delay(1);
	int recv = SDLNet_UDP_Recv(socket, packet);
	if (recv == -1)
	{
	    printf("Broken: %s\n", SDLNet_GetError());
	    throw 999;
	}
	if (recv == 1)
	{
	    printf("Got one!");
	    struct data_sent *data = (struct data_sent*) packet->data;
	    GameLogic *g = (GameLogic*) gameLogic;
	    SDL_LockMutex(g->write_other_players);
	    for (auto &p : g->others)
	    {
		//Todo: Allow multiple other players
		p.x = data->x; p.y = data->y; p.xspd = data->xspd; p.yspd = data->yspd; p.angle = data->angle; p.aspd = data->aspd;
	    }
	    SDL_UnlockMutex(g->write_other_players);
	    }
	}
}

void send_packet(ActivePlayer* play)
{
    struct data_sent data = {play->x, play->y, play->xspd, play->yspd, play->angle, play->aspd, play->left_prev, play->right_prev, play->up_prev};
    packet->data = (Uint8*) &data;
    packet->len = 80;
    printf("Size of data: %i", sizeof(struct data_sent));
    if (SDLNet_UDP_Send(socket, -1, packet) == 0)
    {
	printf("Something went wrong. D:\n");
	throw 44;
    }
    return;	
}
