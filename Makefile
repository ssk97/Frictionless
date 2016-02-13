SOURCES = helloworld.cpp
CC = g++
LFLAGS = -L/usr/lib/x86_64-linux-gnu -lSDL2 
CFLAGS = -Wall -O2 -I/usr/include/SDL2 -D_REENTRANT

all: helloworld

helloworld: $(SOURCES)
	$(CC) -o $@ $(SOURCES) $(LFLAGS) $(CFLAGS)
clean:
	rm helloworld
