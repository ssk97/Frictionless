#pragma once
#include <SDL_net.h>
#define PORT_NUMBER 1028

IPaddress server_begin();
IPaddress client_begin(char*);
void receive_packets();
void send_packet();

