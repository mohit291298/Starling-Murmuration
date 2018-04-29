
CC = g++
CFLAGS = -c
DEBUG = -g
SRCDIR = src
BUILDDIR = build
srctest = test
TARG = bin/starlings-simulation
TARGTEST = bin/starlings-simulation-test
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: boids

boids: $(BUILDDIR)/Boid.o $(BUILDDIR)/Flock.o $(BUILDDIR)/main.o
	$(CC) $(DEBUG) $(BUILDDIR)/Boid.o $(BUILDDIR)/Flock.o $(BUILDDIR)/main.o -o $(TARG) $(SFML)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

.PHONY: clean

tester :
	$(CC) $(CFLAGS) $(DEBUG) test/maintest.cpp -o $(BUILDDIR)/maintest.o;$(CC) $(DEBUG) $(BUILDDIR)/Boid.o $(BUILDDIR)/Flock.o $(BUILDDIR)/maintest.o -o $(TARGTEST) $(SFML)

clean:
	\rm -r $(BUILDDIR)/*.o bin/*

