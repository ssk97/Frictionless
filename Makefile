SOURCES = main.cpp Player.cpp network.cpp GameLogic.cpp Exhaust.cpp RingMaster.cpp Menu.cpp Bumper.cpp
CC = g++
LFLAGS = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_net -lGL 
CFLAGS = -Wall -O2 -I/usr/include/SDL2 -D_REENTRANT -std=c++11 -g

all: frictionless

frictionless: $(SOURCES)
	$(CC) -o $@ $(SOURCES) $(LFLAGS) $(CFLAGS)
clean:
	rm frictionless
