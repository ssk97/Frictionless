SOURCES = network.cpp
CC = g++
LFLAGS = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_net
CFLAGS = -Wall -O2 -I/usr/include/SDL2 -D_REENTRANT -g

all: server client

server: $(SOURCES) server.cpp
	$(CC) -o $@ $(SOURCES) server.cpp $(LFLAGS) $(CFLAGS)

client: $(SOURCES) client.cpp
	$(CC) -o $@ $(SOURCES) client.cpp $(LFLAGS) $(CFLAGS)
clean:
	rm server client
