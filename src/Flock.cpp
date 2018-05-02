#include "../include/Boid.h"
#include "../include/Flock.h"
#include <math.h>
/** @file */
// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

/**
* A Member function which adds the input boid to the flock(std::vector<Boid>).
* @param b The boid to be added.
*/
void Flock::addBoid(Boid b)
{
    flock.push_back(b);
}

/**
* A Member function which returns the boid at index i of the flock.
* This function takes an integer i and returns the boid at that position in the flock.
* A greater index means the boid is added recently(By a mouse click!) in the flock. 
* @param i An int(index).
* @return The boid at index i. 
*/
Boid Flock::getBoid(int i)
{
    return flock[i];
}

/**
* A Member function which updates the behaviour of every single boid w.r.t its neighbourhood.
* It calls the run function in Boid class for every Boid in the Flock. 
* @param a An int to be used by the borders function in Boid.
*/
void Flock::flocking( int a) 
{
	int ct = bt;
	if(bt < 10){
		bt++;
	}
	else{
	energy = 0.0f;
	force = 0.0f;
	angmomentum = 0.0f;
	bt = 0;
	}
	myvector ini;
    for (int i = 0; i < flock.size(); i++){
    	ini.x = flock[i].velocity.x;
    	ini.y = flock[i].velocity.y;
        flock[i].run(flock,a);
        if(ct == 10){
        energy += pow(((flock[i].velocity).magnitude()),2);
        force += (((flock[i].velocity).magnitude()) - ((ini).magnitude()));
        angmomentum += ((((flock[i].location).x)*((flock[i].velocity).y)) - (((flock[i].location).y)*((flock[i].velocity).x)));
    	}
    }
    energy;
}

/**
* A Member function which return the size of the flock.
* @return An int representing the number of Boids in the flock at that instant.
*/
int Flock::getSize()
{
    return flock.size();
}
