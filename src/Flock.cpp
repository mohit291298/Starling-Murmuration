#include "../include/Boid.h"
#include "../include/Flock.h"
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
    for (int i = 0; i < flock.size(); i++)
        flock[i].run(flock,a);
}

/**
* A Member function which return the size of the flock.
* @return An int representing the number of Boids in the flock at that instant.
*/
int Flock::getSize()
{
    return flock.size();
}
