#pragma once
#include <SDL_net.h>
#include "Player.h"
#include <cstdint>
#define PORT_NUMBER 1028

int server_begin(uint32_t* rng_seed, IPaddress* address);
IPaddress client_begin(char*, uint32_t);
int receive_packets(void* ignored);
void send_packet(ActivePlayer* play, Uint8 flagsPassed);

void server_stop();

struct data_sent
{
    double x, y, xspd, yspd, angle, aspd;
    Uint8 left_prev, right_prev, up_prev;
    Uint8 passed_rings;    
    uint32_t rng_seed;
};

