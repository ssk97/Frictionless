#pragma once
#include <SDL_net.h>
#define PORT_NUMBER 1028

void server_begin();
void client_begin(char*);
void receive_packets();
void send_packet();

