#pragma once
#include <SDL_net.h>
#include "Player.h"
#define PORT_NUMBER 1028

IPaddress server_begin();
IPaddress client_begin(char*);
void receive_packets();
void send_packet(ActivePlayer* play);

struct data_sent
{
    double x, y, xspd, yspd, angle, aspd;
    Uint8 left_prev, right_prev, up_prev;
};
