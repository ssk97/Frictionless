#include <stdio.h>
#include "network.h"
#include "globals.h"
#include "GameLogic.h"

#define PACKET_SIZE 10000

UDPsocket socket;
UDPpacket* read_packet;
UDPpacket* write_packet;
IPaddress addr;

IPaddress server_begin(uint32_t* rng_seed)
{
    socket = SDLNet_UDP_Open(PORT_NUMBER);
    if (socket == NULL)
    {
	printf("Could not open socket: %s\n", SDLNet_GetError());
	throw 8;
    }
    read_packet = SDLNet_AllocPacket(PACKET_SIZE);
    write_packet = SDLNet_AllocPacket(PACKET_SIZE);
    int ready = 0;
    while(!ready)
    {
	if(SDLNet_UDP_Recv(socket,read_packet))
	{
	    printf("Got opening connection");

	    struct data_sent *data = (struct data_sent*) read_packet->data;
	    
	    addr = read_packet->address;
	    write_packet->address.host = read_packet->address.host;
	    write_packet->address.port = read_packet->address.port;
	    *rng_seed = data->rng_seed;
	    ready = 1;
	}
    }
    return read_packet->address;
}

IPaddress client_begin(char* hostname, uint32_t rng_seed)
{
    socket = SDLNet_UDP_Open(0);
    if (socket == NULL)
    {
	printf("Could not open socket: %s\n", SDLNet_GetError());    
	throw 445;
    }
    SDLNet_ResolveHost(&addr, hostname, PORT_NUMBER);
    read_packet = SDLNet_AllocPacket(PACKET_SIZE);
    write_packet = SDLNet_AllocPacket(PACKET_SIZE);    
    if (!write_packet)
    {
	printf("Invalid packet.\n");
	throw 15;
    }
    write_packet->address.host = addr.host;
    write_packet->address.port = PORT_NUMBER;
    //TODO: Transmit some real information over the wire.
    struct data_sent data = {0, 0, 0, 0, 0, 0, 0, 0, 0, rng_seed};
    write_packet->len = sizeof(data);

    if (SDLNet_UDP_Send(socket, -1, write_packet) == 0)
    {
	printf("Something went wrong: %s\n", SDLNet_GetError());
	throw 4454;
    }
    return write_packet->address;
}

//This needs to be run in a seperate thread.
int receive_packets(void* gameLogic)
{
    printf("Starting to recieve packets.\n");
    while(1)
    {
    SDL_Delay(1);
    int recv = SDLNet_UDP_Recv(socket, read_packet);
    if (recv == -1)
    {
        printf("Broken: %s\n", SDLNet_GetError());
        throw 999;
    }
    if (recv == 1)
    {
        struct data_sent *data = (struct data_sent*) read_packet->data;
        GameLogic *g = (GameLogic*) gameLogic;
        SDL_LockMutex(g->write_other_players);
        for (auto &p : g->others)
        {
	    //Todo: Allow multiple other players
	    p.x = data->x; p.y = data->y; p.xspd = data->xspd; p.yspd = data->yspd; p.angle = data->angle; p.aspd = data->aspd; p.left_btn = data->left_prev; p.right_btn = data->right_prev; p.up_btn = data->up_prev;
        }
        SDL_UnlockMutex(g->write_other_players);
    }
    }
}

void send_packet(ActivePlayer* play)
{
    struct data_sent data = {play->x, play->y, play->xspd, play->yspd, play->angle, play->aspd, play->left_btn, play->right_btn, play->up_btn};
    write_packet->data = (Uint8*) &data;
    write_packet->len = 80;
    if (SDLNet_UDP_Send(socket, -1, write_packet) == 0)
    {
	printf("Something went wrong. D:\n");
	throw 44;
    }
    return;    
}
