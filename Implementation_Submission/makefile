
CC = g++
CFLAGS = -c
DEBUG = -g
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: boids

boids: Boid.o Flock.o main.o
	$(CC) $(DEBUG) Boid.o Flock.o main.o -o starlings-simulation $(SFML)

Boid.o : Boid.cpp
	$(CC) $(CFLAGS) $(DEBUG) Boid.cpp

Flock.o : Flock.cpp
	$(CC) $(CFLAGS) $(DEBUG) Flock.cpp

clean:
	\rm *.o starlings-simulation

tar:
	tar cfv boids.tar Boid.h Boid.cpp \
		Flock.h Flock.cpp
