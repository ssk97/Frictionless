#pragma once
#include <SDL_net.h>
#pragma once
#include "Player.h"
#define PORT_NUMBER 1028

IPaddress server_begin();
IPaddress client_begin(char*);
int receive_packets(void* ignored);
void send_packet(ActivePlayer* play);

struct data_sent
{
    double x, y, xspd, yspd, angle, aspd;
    Uint8 left_prev, right_prev, up_prev;
};

